#pragma once

class Sensor
{
public:
    Sensor();

    void setPaperDetected(bool detected);
    bool isPaperDetected() const;

private:
    bool paperDetected;
};