#pragma once

#define AUWND_EXCEPT(hr) Win32_Window::HrException(__LINE__, __FILE__, hr)
#define AUWND_LAST_EXCEPT() Win32_Window::HrException(__LINE__, __FILE__, GetLastError())
#define AUWND_NOGFX_EXCEPT() Win32_Window::NoGfxException( __LINE__,__FILE__ )