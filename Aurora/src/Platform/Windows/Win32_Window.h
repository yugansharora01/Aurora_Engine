#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "AuroraWin.h"
#include "AuroraException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

namespace Aurora {

    class Win32_Window
    {
    public:
        class Exception : public AuroraException
        {
            using AuroraException::AuroraException;
        public:
            static std::string TranslateErrorCode(HRESULT hr) noexcept;
        };
        class HrException : public Exception
        {
        public:
            HrException(int line, const char* file, HRESULT hr);
            const char* what() const noexcept override;
            const char* GetType() const noexcept override;
            HRESULT GetErrorCode() const noexcept;
            std::string GetErrorString() const noexcept;

        private:
            HRESULT hr;
        };

        class NoGfxException : public Exception
        {
        public:
            using Exception::Exception;
            const char* GetType() const noexcept override;
        };

    private:
        //Singleton manages registration/cleanup of window class
        class WindowClass
        {
        public:
            static const char* GetName() noexcept;
            static HINSTANCE GetInstance() noexcept;

        private:
            WindowClass() noexcept;
            ~WindowClass();
            WindowClass(const WindowClass&) = delete;
            WindowClass& operator=(const WindowClass&) = delete;
            static constexpr const char* wndClassName = "Direct3D Engine Window";
            static WindowClass wndClass;
            HINSTANCE hInst;
        };

    public:
        Win32_Window(int width, int height, const char* name);
        ~Win32_Window();
        Win32_Window(const Win32_Window&) = delete;
        Win32_Window& operator=(const Win32_Window&) = delete;
        static Win32_Window* Create(int width, int height, const char* name);
        void SetTitle(const std::string& title);
        static std::optional<int> ProcessMessages();
        void Destroy();
        Graphics& Gfx();
        inline HWND GetHandle() noexcept { return hWnd; }
        void GetWindowSize(unsigned int& width, unsigned int& height) noexcept;
        void SetViewPort(unsigned int width, unsigned int height) { pGfx->SetViewPort(width,height); }


    private:
        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    public:
        Keyboard kbd;
        Mouse mouse;
        std::unique_ptr<Graphics> pGfx;

    private:
        int width;
        int height;
        HWND hWnd;
        int m_finalWidth;
        int m_finalHeight;
    };
}

#endif // WINDOW_H_INCLUDED
