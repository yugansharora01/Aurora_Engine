#include "pch.h"
#include "Keyboard.h"
#include "Aurora/Log.h"

namespace Aurora {

    bool Keyboard::IsKeyPressed(unsigned char keycode) const noexcept
    {
        return keyStates[keycode];
    }

    void Keyboard::EnableAutorepeat() noexcept
    {
        autorepeatEnabled = true;
    }

    void Keyboard::DisableAutorepeat() noexcept
    {
        autorepeatEnabled = false;
    }

    bool Keyboard::IsAutorepeatEnabled() noexcept
    {
        return autorepeatEnabled;
    }

    void Keyboard::OnKeyPressed(unsigned char keycode) noexcept
    {
        keyStates[keycode] = true;
    }

    void Keyboard::OnKeyReleased(unsigned char keycode) noexcept
    {
        keyStates[keycode] = false;
    }

    void Keyboard::OnChar(char character) noexcept
    {
    }


    void Keyboard::ClearState() noexcept
    {
        keyStates.reset();
    }

    
}
