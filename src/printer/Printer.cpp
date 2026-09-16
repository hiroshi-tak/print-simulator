#include "Printer.h"

Printer::Printer(PrinterDevice *device)
{
    this->state = PrinterState::IDLE;
    this->device = device;
}

void Printer::startPrint()
{
    if (this->state == PrinterState::IDLE ||
        this->state == PrinterState::STOPPED)
    {
        if (this->sensor.isPaperDetected())
        {
            this->motor.start();
            this->state = PrinterState::PRINTING;

            this->device->print();
        }
    }
}

void Printer::stopPrint()
{
    if (this->state == PrinterState::PRINTING)
    {
        this->motor.stop();
        this->state = PrinterState::STOPPED;
    }
}

void Printer::finishPrint()
{
    if (this->state == PrinterState::PRINTING)
    {
        this->motor.stop();
        this->state = PrinterState::IDLE;
    }
}

PrinterState Printer::getState() const
{
    return this->state;
}

bool Printer::isMotorRunning() const
{
    return this->motor.isRunning();
}