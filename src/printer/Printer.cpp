#include "Printer.h"

Printer::Printer(PrinterDevice *device)
{
    this->state = PrinterState::IDLE;
    this->error = PrinterError::NONE;
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

PrinterError Printer::getError() const
{
    return this->error;
}

void Printer::setError(PrinterError error)
{
    this->error = error;
    this->state = PrinterState::ERROR;
    this->motor.stop();
}

void Printer::clearError()
{
    this->error = PrinterError::NONE;
    this->state = PrinterState::IDLE;
}

bool Printer::isMotorRunning() const
{
    return this->motor.isRunning();
}

void Printer::setPaperDetected(bool detected)
{
    this->sensor.setPaperDetected(detected);
}

void Printer::setPaperJamDetected(bool detected)
{
    this->sensor.setPaperJamDetected(detected);

    if (detected)
    {
        this->setError(PrinterError::PAPER_JAM);
    }
}