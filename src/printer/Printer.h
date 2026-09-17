#pragma once

#include "PrinterState.h"
#include "PrinterError.h"
#include "PrintJob.h"

#include "hardware/Motor.h"
#include "hardware/Sensor.h"
#include "hardware/Timer.h"
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
    void setPaperJamDetected(bool detected);

    int getRemainingAmount() const;
    bool consumePrintAmount(int amount);

    void createPrintJob(int copies);
    bool executePrintJob();

    int getTotalCopies() const;
    int getRemainingCopies() const;

    void startTimer(int seconds);
    void tickTimer();

private:
    PrinterState state;
    PrinterError error;

    Motor motor;
    Sensor sensor;
    PrintJob printJob;
    Timer timer;

    PrinterDevice *device;
};