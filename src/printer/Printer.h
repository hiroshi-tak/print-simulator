#pragma once

#include "PrinterState.h"
#include "PrinterError.h"
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

    PrinterError getError() const;
    void setError(PrinterError error);
    void clearError();

    bool isMotorRunning() const;

    void setPaperDetected(bool detected);

private:
    PrinterState state;
    PrinterError error;
    
    Motor motor;
    Sensor sensor;
    PrinterDevice *device;
};