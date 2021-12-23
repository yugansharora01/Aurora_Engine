#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

namespace Aurora {

    class Mouse
    {
        friend class Win32_Window;

    public:
       

    public:
        Mouse() = default;
        Mouse(const Mouse&) = delete;
        Mouse& operator=(const Mouse&) = delete;
        std::pair<int, int> GetPos() const noexcept;
        int GetPosX() const noexcept;
        int GetPosY() const noexcept;
        bool IsInWindow() const noexcept;
        bool IsLeftPressed() const noexcept;
        bool IsRightPressed() const noexcept;

    private:
        void OnMouseMove(int x, int y) noexcept;
        void OnMouseLeave() noexcept;
        void OnMouseEnter() noexcept;
        void OnLeftPressed(int x, int y) noexcept;
        void OnLeftReleased(int x, int y) noexcept;
        void OnRightPressed(int x, int y) noexcept;
        void OnRightReleased(int x, int y) noexcept;
        void OnWheelUp(int x, int y) noexcept;
        void OnWheelDown(int x, int y) noexcept;
        void OnWheelDelta(int x, int y, int delta) noexcept;

    private:
        static constexpr unsigned int bufferSize = 16u;
        int x;
        int y;
        bool leftIsPressed = false;
        bool rightIsPressed = false;
        bool isInWindow = false;
        int wheelDeltaCarry = 0;
    };
}

#endif // MOUSE_H_INCLUDED
