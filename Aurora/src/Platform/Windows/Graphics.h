#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "AuroraWin.h"
#include "AuroraException.h"
#include "DxgiInfoManager.h"

#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
 
#include <random>

namespace Aurora {
    class Graphics
    {
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
        Graphics(HWND hWnd);
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;
        ~Graphics() = default;
        void EndFrame();
        void ClearBuffer(float red, float green, float blue) noexcept;
        void DrawIndexed(unsigned int count) AU_DEBUGNOEXCEPT;
        void SetProjection(DirectX::FXMMATRIX proj) noexcept;
        static DirectX::XMMATRIX GetProjection() noexcept;

        inline Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return pDevice; }
        inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetContext() { return pContext; }
        inline Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetTarget() { return pTarget; }
        inline Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencil() { return pDSV; }
        inline DxgiInfoManager& GetInfoManager() { return infoManager; }

    private:
        static DirectX::XMMATRIX projection;

    private:
#ifndef NDEBUG
        DxgiInfoManager infoManager;
#endif // !NDEBUG

        Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
        Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
    };
}
#endif // GRAPHICS_H_INCLUDED
