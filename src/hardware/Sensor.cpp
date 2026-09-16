#include "Sensor.h"

Sensor::Sensor()
{
    this->paperDetected = true;
}

void Sensor::setPaperDetected(bool detected)
{
    this->paperDetected = detected;
}

bool Sensor::isPaperDetected() const
{
    return this->paperDetected;
}