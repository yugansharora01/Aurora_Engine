#include "pch.h"
#include "Win32_Window.h"
#include "WindowsThrowMacros.h"

#include "Aurora/Application.h"
#include "Aurora/Window.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Aurora/Renderer/FrameBuffer.h"
#include "Aurora/Events/ApplicationEvents.h"
#include "Aurora/Events/KeyboardEvents.h"
#include "Aurora/Events/MouseEvents.h"

#include <backends/imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Aurora {

    Win32_Window::WindowClass Win32_Window::WindowClass::wndClass;

    std::string Win32_Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
    {
        char* pMsgBuf = nullptr;
        DWORD nMsgLen = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&pMsgBuf),
            0, nullptr);

        if (nMsgLen == 0)
            return "undefined Error code";

        std::string errorString = pMsgBuf;
        LocalFree(pMsgBuf);
        return errorString;
    }

    Win32_Window::HrException::HrException(int line, const char* file, HRESULT hr)
        : Exception(line, file), hr(hr)
    {
    }

    const char* Win32_Window::HrException::what() const noexcept
    {
        std::ostringstream oss;
        oss << GetType() << std::endl
            << "[Error Code]" << GetErrorCode() << std::endl
            << "[Description]" << GetErrorString() << std::endl
            << GetOriginString();
        whatBuffer = oss.str();
        return whatBuffer.c_str();
    }

    const char* Win32_Window::HrException::GetType() const noexcept
    {
        return "Aurora Window Exception";
    }

    HRESULT Win32_Window::HrException::GetErrorCode() const noexcept
    {
        return hr;
    }

    std::string Win32_Window::HrException::GetErrorString() const noexcept
    {
        return TranslateErrorCode(hr);
    }

    Win32_Window::WindowClass::WindowClass() noexcept
        : hInst(GetModuleHandle(nullptr))
    {
        WNDCLASSEXA wc = { 0 };
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = HandleMsgSetup;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = GetInstance();
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = GetName();
        wc.hIconSm = nullptr;

        //Register window class
        RegisterClassExA(&wc);
    }

    Win32_Window::WindowClass::~WindowClass()
    {
        UnregisterClassA(wndClassName, GetInstance());
    }

    const char* Win32_Window::WindowClass::GetName() noexcept
    {
        return wndClassName;
    }

    HINSTANCE Win32_Window::WindowClass::GetInstance() noexcept
    {
        return wndClass.hInst;
    }

    Win32_Window::Win32_Window(int width, int height, const char* name)
        : width(width), height(height)
    {
        RECT wr;
        wr.left = 100;
        wr.right = width + wr.left;
        wr.top = 100;
        wr.bottom = height + wr.top;
        if (AdjustWindowRect(&wr, WS_SIZEBOX | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX, FALSE) == 0)
        {
            throw AUWND_LAST_EXCEPT();
        }

        m_finalWidth = wr.right - wr.left;
        m_finalHeight = wr.bottom - wr.top;

        /*hWnd = CreateWindow(WindowClass::GetName(), name, WS_SIZEBOX| WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, m_finalWidth, m_finalHeight,
            nullptr, nullptr, WindowClass::GetInstance(), this);*/

        hWnd = CreateWindowEx(0,WindowClass::GetName(), name, WS_SIZEBOX | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, m_finalWidth, m_finalHeight,
            nullptr, nullptr, WindowClass::GetInstance(), this);

        //Check for error
        if (hWnd == nullptr)
        {
            throw AUWND_LAST_EXCEPT();
        }
        // newly created window starts off as hidden
        ShowWindow(hWnd, SW_SHOWDEFAULT);

        
    }
    Win32_Window::~Win32_Window()
    {
        Destroy();
    }

    Win32_Window* Win32_Window::Create(int width, int height, const char* name)
    {
        return new Win32_Window(width, height, name);
    }

    void Win32_Window::SetTitle(const std::string& title)
    {
        if (SetWindowTextA(hWnd, title.c_str()) == 0)
        {
            throw AUWND_LAST_EXCEPT();
        }
    }

    std::optional<int> Win32_Window::ProcessMessages()
    {
        MSG msg;
        //While queue has messages , remove and dispatch them (but do not block the loop)
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //check for quit because peekmessage does not signal this via return value
            if (msg.message == WM_QUIT)
            {
                // return optional wrapping int (arg to PostQuitMessage is in wParam)
                return msg.wParam;
            }

            // TranslateMessage will post auxillary WM_CHAR messages from key message
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // return empty optional when not quiting app
        return {};
    }

    void Win32_Window::Destroy()
    {
        DestroyWindow(hWnd);
    }

    void Win32_Window::GetWindowSize(unsigned int& width, unsigned int& height) noexcept
    {
        width = this->width;
        height = this->height;

    }

    void Win32_Window::Resize(unsigned int width, unsigned int height)
    {
        /*if (Application::Get().IsSetupDone)
        {
            dynamic_cast<WindowsWindow*>(&Application::Get().GetWindow())->SetWindowData(width, height);
            std::dynamic_pointer_cast<D3D11Graphics>(Application::Get().GetWindow().Gfx())->Recreate(hWnd, width, height);
            Application::Get().GetWindow().Gfx()->fbuf = FrameBuffer::Create(width, height);
        }*/
    }

    LRESULT CALLBACK Win32_Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Win32_Window* const pWnd = static_cast<Win32_Window*>(pCreate->lpCreateParams);

            //set WinAPI managed user data to store ptr to window class
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

            //set message proc to normal (non-setup) handle now that setup is finished
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32_Window::HandleMsgThunk));

            //forward the message to window class handler
            return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
        }
        //if we get a message before the WM_NCCREATE
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Win32_Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        //Retrieve ptr to window class
        Win32_Window* const pWnd = reinterpret_cast<Win32_Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        //forward message to window class handler
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    LRESULT Win32_Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        {
            return true;
        }

        

        switch (msg)
        {
        case WM_SIZE:
        {
            if (LOWORD(lParam) != 0 && HIWORD(lParam) != 0)
            {
                width = LOWORD(lParam);
                height = HIWORD(lParam);
                WindowResizeEvent event(width,height);
                Application::Get().OnEvent(event);
                Resize(width, height);
            }
            break;
        }
        case WM_CLOSE:
        {
            WindowCloseEvent WinCloseEvent;
            Application::Get().OnEvent(WinCloseEvent);
            PostQuitMessage(0);
            return 0;
        }            
        case WM_KILLFOCUS:
        {
            kbd.ClearState();
            break;
        }
            /************* Keyboard Messages *******************/
        case WM_KEYDOWN:
            // syskey commands need to be handled to track ALT key (VK_MENU) and F10
        case WM_SYSKEYDOWN:
        {
            if (!(lParam & 0x40000000) || kbd.IsAutorepeatEnabled())
                kbd.OnKeyPressed(static_cast<unsigned char>(wParam));

            KeyPressedEvent KeyPressEvent(static_cast<int>(wParam), 0);
            Application::Get().OnEvent(KeyPressEvent);
            break;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            kbd.OnKeyReleased(static_cast<unsigned char>(wParam));

            KeyReleasedEvent KeyRelEvent(static_cast<int>(wParam));
            Application::Get().OnEvent(KeyRelEvent);
            break;
        }
        case WM_CHAR:
        {
            kbd.OnChar(static_cast<unsigned char>(wParam));

            KeyTypedEvent KeyTypeEvent(static_cast<int>(wParam));
            Application::Get().OnEvent(KeyTypeEvent);
            break;
        }
            /************* End of Keyboard Messages ******************/
            /*************** Mouse Messages ********************/
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            // in client region -> log move, and log enter + capture mouse (if not previously in window)
            if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
            {
                mouse.OnMouseMove(pt.x, pt.y);
                MouseMovedEvent MouseMoveEvent(pt.x, pt.y);
                Application::Get().OnEvent(MouseMoveEvent);
                if (!mouse.IsInWindow())
                {
                    SetCapture(hWnd);
                    mouse.OnMouseEnter();
                }
            }
            // not in client -> log move / maintain capture if button down
            else
            {
                if (wParam & (MK_LBUTTON | MK_RBUTTON))
                {
                    mouse.OnMouseMove(pt.x, pt.y);
                    MouseMovedEvent MouseMoveEvent(pt.x, pt.y);
                    Application::Get().OnEvent(MouseMoveEvent);
                }
                // button up -> release capture / log event for leaving
                else
                {
                    ReleaseCapture();
                    mouse.OnMouseLeave();
                }
            }
            break;
        }
        case WM_LBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftPressed(pt.x, pt.y);
            MouseButtonPressedEvent MouseLButtonPressEvent(MouseButtonEvent::MouseButtons::LeftButton);
            Application::Get().OnEvent(MouseLButtonPressEvent);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightPressed(pt.x, pt.y);
            MouseButtonPressedEvent MouseRButtonPressEvent(MouseButtonEvent::MouseButtons::RightButton);
            Application::Get().OnEvent(MouseRButtonPressEvent);
            break;
        }
        case WM_LBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftReleased(pt.x, pt.y);
            MouseButtonReleasedEvent MouseLButtonReleaseEvent(MouseButtonEvent::MouseButtons::LeftButton);
            Application::Get().OnEvent(MouseLButtonReleaseEvent);
            break;
        }
        case WM_RBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightReleased(pt.x, pt.y);
            MouseButtonReleasedEvent MouseRButtonReleaseEvent(MouseButtonEvent::MouseButtons::RightButton);
            Application::Get().OnEvent(MouseRButtonReleaseEvent);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            mouse.OnWheelDelta(pt.x, pt.y, delta);
            MouseScrolledEvent event((float)delta,(float)delta);
            Application::Get().OnEvent(event);
        }
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    const char* Win32_Window::NoGfxException::GetType() const noexcept
    {
        return "Aurora Window Exception [No Graphics]";
    }
}