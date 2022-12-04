#include "pch.h"
#include "Keyboard.h"

namespace Aurora {

    bool Keyboard::IsKeyPressed(unsigned char keycode) const noexcept
    {
        return keyStates[keycode];
    }

    bool Keyboard::IsAnotherKeyPressed(unsigned char keycode) const noexcept
    {
        for (auto i = 0;i < nKeys;i++)
        {
            if (keyStates[i] == 1 && i != keycode)
                return true;
        }
        return false;
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
