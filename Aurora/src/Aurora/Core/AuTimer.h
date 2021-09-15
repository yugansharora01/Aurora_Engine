#ifndef AUTIMER_H_INCLUDED
#define AUTIMER_H_INCLUDED


class AuTimer
{
public : 
    AuTimer();
    float Mark();
    float Peek() const noexcept;
private:
    std::chrono::steady_clock::time_point last;
};

#endif // AUTIMER_H_INCLUDED
