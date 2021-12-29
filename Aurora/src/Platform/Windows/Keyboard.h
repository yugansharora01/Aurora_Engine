#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

namespace Aurora {

    class Keyboard
    {
        friend class Win32_Window;

    public:
        Keyboard() = default;
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;

        //Key Event stuff
        bool IsKeyPressed(unsigned char keycode) const noexcept;
        bool IsAnotherKeyPressed(unsigned char keycode) const noexcept;

        //Autorepeat control
        void EnableAutorepeat() noexcept;
        void DisableAutorepeat() noexcept;
        bool IsAutorepeatEnabled() noexcept;

    private:
        void OnKeyPressed(unsigned char keycode) noexcept;
        void OnKeyReleased(unsigned char keycode) noexcept;
        void OnChar(char character) noexcept;
        void ClearState() noexcept;

    private:
        static constexpr unsigned int nKeys = 256u;
        bool autorepeatEnabled = false;
        std::bitset<nKeys> keyStates;
    };
}

#endif // KEYBOARD_H_INCLUDED
