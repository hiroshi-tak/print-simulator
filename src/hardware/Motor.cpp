#include "Motor.h"

Motor::Motor()
{
    this->running = false;
}

void Motor::start()
{
    this->running = true;
}

void Motor::stop()
{
    this->running = false;
}

bool Motor::isRunning() const
{
    return this->running;
}