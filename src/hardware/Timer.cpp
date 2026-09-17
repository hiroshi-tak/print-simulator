#include "Timer.h"

Timer::Timer()
{
    this->running = false;
    this->remainingSeconds = 0;
}

void Timer::start(int seconds)
{
    this->running = true;
    this->remainingSeconds = seconds;
}

void Timer::stop()
{
    this->running = false;
    this->remainingSeconds = 0;
}

void Timer::tick()
{
    if (!this->running)
    {
        return;
    }

    if (this->remainingSeconds > 0)
    {
        this->remainingSeconds--;
    }
}

bool Timer::isExpired() const
{
    return this->running &&
           this->remainingSeconds == 0;
}