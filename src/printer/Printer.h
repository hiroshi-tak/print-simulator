#pragma once

#include "PrinterState.h"
#include "hardware/Motor.h"
#include "hardware/Sensor.h"
#include "device/PrinterDevice.h"

class Printer
{
public:
    Printer(PrinterDevice *device);

    void startPrint();
    void stopPrint();
    void finishPrint();

    PrinterState getState() const;
    bool isMotorRunning() const;

private:
    PrinterState state;
    Motor motor;
    Sensor sensor;
    PrinterDevice *device;
};