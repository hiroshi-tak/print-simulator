#include "Sensor.h"

Sensor::Sensor()
{
    this->paperDetected = true;
    this->paperJamDetected = false;
}

void Sensor::setPaperDetected(bool detected)
{
    this->paperDetected = detected;
}

bool Sensor::isPaperDetected() const
{
    return this->paperDetected;
}

void Sensor::setPaperJamDetected(bool detected)
{
    this->paperJamDetected = detected;
}

bool Sensor::isPaperJamDetected() const
{
    return this->paperJamDetected;
}