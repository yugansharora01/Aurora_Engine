#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "Platform/Windows/AuroraWin.h"
#include "Platform/Windows/AuroraException.h"
#include "Platform/Windows/DxgiInfoManager.h"
#include "Aurora/Core/Graphics.h"

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
 
#include <random>

namespace Aurora {

    class D3D11FrameBuffer;
    class Graphics;

    class D3D11Graphics : public Graphics
    {
        friend class D3D11FrameBuffer;
    public:
        class Exception : public AuroraException
        {
            using AuroraException::AuroraException;
        };

        class HrException : public Exception
        {
        public:
            HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
            const char* what() const noexcept override;
            const char* GetType() const noexcept override;
            HRESULT GetErrorCode() const noexcept;
            std::string GetErrorString() const noexcept;
            std::string GetErrorDescription() const noexcept;
            std::string GetErrorInfo() const noexcept;

        private:
            HRESULT hr;
            std::string info;
        };

        class InfoException : public Exception
        {
        public:
            InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
            const char* what() const noexcept override;
            const char* GetType() const noexcept override;
            std::string GetErrorInfo() const noexcept;
        private:
            std::string info;
        };

        class DeviceRemovedException : public HrException
        {
            using HrException::HrException;

        public:
            const char* GetType() const noexcept override;
        private:
            std::string reason;
        };

    public:
        D3D11Graphics() = default;
        D3D11Graphics(HWND hWnd,unsigned int width = 800u,unsigned int height = 600u);
        D3D11Graphics(const D3D11Graphics&) = delete;
        D3D11Graphics& operator=(const D3D11Graphics&) = delete;
        ~D3D11Graphics() = default;

        virtual void EndFrame() override;
        virtual void ClearBuffer(float red, float green, float blue) noexcept override;
        virtual void DrawIndexed(unsigned int count) AU_RELEASENOEXCEPT override;
        virtual void SetViewPort(unsigned int width, unsigned int height) override;
        virtual void RenderToTex() override;
        virtual void Resize(unsigned int width = 800u, unsigned int height = 600u) override;

        inline Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return pDevice; }
        inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() { return pContext; }
        inline Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwap() { return pSwap; }
        inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetTarget() { return pTarget; }
        inline Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return pDSV; }
        
#ifndef AU_RELEASE
        inline DxgiInfoManager& GetInfoManager() { return infoManager; }
#endif // AU_RELEASE

    private:
#ifndef AU_RELEASE
        DxgiInfoManager infoManager;
#endif // AU_RELEASE

        Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
        Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;

        HWND hwnd;
    };
}
#endif // GRAPHICS_H_INCLUDED
