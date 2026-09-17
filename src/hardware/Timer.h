#pragma once

class Timer
{
public:
    Timer();

    void start(int seconds);
    void stop();
    void tick();

    bool isExpired() const;

private:
    bool running;
    int remainingSeconds;
};