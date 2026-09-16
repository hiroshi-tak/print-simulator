#pragma once

class Motor
{
public:
    Motor();

    void start();
    void stop();

    bool isRunning() const;

private:
    bool running;
};