#include "Sensor.h"

Sensor::Sensor()
{
    this->paperDetected = true;
    this->paperJamDetected = false;
}

void Sensor::setPaperDetected(bool detected)
{
    std::lock_guard<std::mutex> lock(this->mutex);

    this->paperDetected = detected;
}

bool Sensor::isPaperDetected() const
{
    std::lock_guard<std::mutex> lock(this->mutex);

    return this->paperDetected;
}

void Sensor::setPaperJamDetected(bool detected)
{
    std::lock_guard<std::mutex> lock(this->mutex);

    this->paperJamDetected = detected;
}

bool Sensor::isPaperJamDetected() const
{
    std::lock_guard<std::mutex> lock(this->mutex);

    return this->paperJamDetected;
}