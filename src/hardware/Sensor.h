#pragma once

#include <mutex>

class Sensor
{
public:
    Sensor();

    void setPaperDetected(bool detected);
    bool isPaperDetected() const;

    void setPaperJamDetected(bool detected);
    bool isPaperJamDetected() const;

private:
    bool paperDetected;
    bool paperJamDetected;

    mutable std::mutex mutex;
};