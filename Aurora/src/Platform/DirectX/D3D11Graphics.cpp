#include "pch.h"
#include "D3D11Graphics.h"
#include "Platform/Windows/dxerr.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Platform/Windows/WindowsThrowMacros.h"

#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"


#include "Aurora/Log.h"
#include "Platform/DirectX/D3D11RenderTargetManager.h"

#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dxgi.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib,"DXGI.lib")

namespace Aurora 
{

    D3D11Graphics::D3D11Graphics(HWND hWnd, unsigned int width, unsigned int height)
        :hwnd(hWnd)
    {
        AU_INFO("Initialised D3D11Graphics");

        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 0;
        sd.BufferDesc.RefreshRate.Denominator = 0;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.OutputWindow = hWnd;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags = 0;

        UINT swapCreateFlags = 0u;
#ifdef AU_DEBUG
        swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !AU_DEBUG


        //for checking results of d3d functions
        HRESULT hr;

        //Create device, front/back buffers, swap chain and rendering context
        GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            swapCreateFlags,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &sd,
            &pSwap,
            &pDevice,
            nullptr,
            &pContext));
                
        SetViewPort(width, height);
    }

    void D3D11Graphics::EndFrame()
    {
        HRESULT hr;
        #ifdef AU_DEBUG
            infoManager.Set();
        #endif // !AU_DEBUG     

        if (FAILED(hr = pSwap->Present(1u, 0u)))
        {
            if (hr == DXGI_ERROR_DEVICE_REMOVED)
            {
                throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
            }
            else
            {
                throw GFX_EXCEPT(hr);
            }
        }

    }

    void D3D11Graphics::ClearBuffer(float red, float green, float blue) noexcept
    {
        const float color[] = { red, green, blue, 1.0f };
        pContext->ClearRenderTargetView(pTarget.Get(), color);
        pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
    }

    void D3D11Graphics::DrawIndexed(UINT count) AU_RELEASENOEXCEPT
    {
        GFX_THROW_INFO_ONLY(pContext->DrawIndexed(count, 0u, 0u));
    }


    void D3D11Graphics::SetViewPort(unsigned int width, unsigned int height)
    {
        // configure viewport
        D3D11_VIEWPORT vp;
        vp.Width = (float)width;
        vp.Height = (float)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;
        pContext->RSSetViewports(1u, &vp);

        AU_CORE_INFO("D3D11Graphics : width = {0}, Height = {1}", width, height); 
    }

    

    void Aurora::D3D11Graphics::Resize(unsigned int width, unsigned int height)
    {
        AU_CORE_INFO("Recreated SwapChain");

        HWND hWnd = hwnd;

        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 0;
        sd.BufferDesc.RefreshRate.Denominator = 0;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;
        sd.OutputWindow = hWnd;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        sd.Flags = 0;

        UINT swapCreateFlags = 0u;
#ifdef AU_DEBUG
        swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !AU_DEBUG


        //for checking results of d3d functions
        HRESULT hr;

        Microsoft::WRL::ComPtr<IDXGIFactory> factory;

        GFX_THROW_INFO(CreateDXGIFactory(__uuidof(IDXGIFactory), &factory));
        
        //Create swap chain
        GFX_THROW_INFO(factory->CreateSwapChain(pDevice.Get(),&sd,&pSwap));

        SetViewPort(width, height);
        
    }

    D3D11Graphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
        :Exception(line, file), hr(hr)
    {
        // join all info messages with newlines into single string
        for (const auto& m : infoMsgs)
        {
            info += m;
            info.push_back('\n');
        }

        AU_CORE_ERROR("{0}", info);
        // remove final newline if exists
        if (!info.empty())
        {
            info.pop_back();
        }
    }

    const char* D3D11Graphics::HrException::what() const noexcept
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
            << std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
            << "[Error String] " << GetErrorString() << std::endl
            << "[Description] " << GetErrorDescription() << std::endl;
        if (!info.empty())
        {
            oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
        }
        oss << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

    const char* D3D11Graphics::HrException::GetType() const noexcept
    {
        return "Aurora D3D11Graphics Exception";
    }

    HRESULT D3D11Graphics::HrException::GetErrorCode() const noexcept
    {
        return hr;
    }

    std::string D3D11Graphics::HrException::GetErrorString() const noexcept
    {
        return DXGetErrorString(hr);
    }

    std::string D3D11Graphics::HrException::GetErrorDescription() const noexcept
    {
        char buf[512];
        DXGetErrorDescription(hr, buf, sizeof(buf));
        return buf;
    }

    std::string D3D11Graphics::HrException::GetErrorInfo() const noexcept
    {
        return info;
    }

    Aurora::D3D11Graphics::DeviceRemovedException::DeviceRemovedException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
        :HrException(line,file,hr,infoMsgs)
    {
        //((D3D11Graphics*)&Application::Get().GetWindow().Gfx())->GetDevice()->GetDeviceRemovedReason();
        //((D3D11Graphics*)&Application::Get().GetWindow().Gfx())->GetDevice()->CreateNewDevice();
    }

    const char* D3D11Graphics::DeviceRemovedException::GetType() const noexcept
    {
        return "Aurora D3D11Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
    }


    D3D11Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
        :
        Exception(line, file)
    {
        // join all info messages with newlines into single string
        for (const auto& m : infoMsgs)
        {
            info += m;
            info.push_back('\n');
        }
        // remove final newline if exists
        if (!info.empty())
        {
            info.pop_back();
        }
    }


    const char* D3D11Graphics::InfoException::what() const noexcept
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
        oss << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

    const char* D3D11Graphics::InfoException::GetType() const noexcept
    {
        return "Aurora D3D11Graphics Info Exception";
    }

    std::string D3D11Graphics::InfoException::GetErrorInfo() const noexcept
    {
        return info;
    }
}