#include "Printer.h"
#include "logger/Logger.h"

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
            Logger::info("印刷を開始します");

            this->motor.start();
            this->state = PrinterState::PRINTING;
        }
        else
        {
            Logger::warning("用紙がありません");
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
    this->sensor.setPaperJamDetected(false);

    this->error = PrinterError::NONE;
    this->state = PrinterState::IDLE;

    Logger::info("エラーから復旧しました");
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

int Printer::getRemainingAmount() const
{
    return this->device->getRemainingAmount();
}

bool Printer::consumePrintAmount(int amount)
{
    if (this->device->getRemainingAmount() < amount)
    {
        this->setError(PrinterError::INK_EMPTY);
        return false;
    }

    this->device->consumeAmount(amount);

    return true;
}

void Printer::createPrintJob(int copies)
{
    this->printJob.create(copies);
}

bool Printer::executePrintJob()
{
    if (!this->printJob.hasJob())
    {
        return false;
    }

    if (this->state != PrinterState::PRINTING)
    {
        return false;
    }

    if (this->device->getRemainingAmount() <= 0)
    {
        this->setError(PrinterError::INK_EMPTY);
        return false;
    }

    if (!this->printJob.printOne())
    {
        return false;
    }

    this->device->print();
    this->device->consumeAmount(1);

    return true;
}

int Printer::getTotalCopies() const
{
    return this->printJob.getTotalCopies();
}

int Printer::getRemainingCopies() const
{
    return this->printJob.getRemainingCopies();
}

void Printer::startTimer(int seconds)
{
    this->timer.start(seconds);
}

void Printer::tickTimer()
{
    this->timer.tick();

    if (!this->timer.isExpired())
    {
        return;
    }

    // Sensorから紙詰まり状態を確認
    if (this->sensor.isPaperJamDetected())
    {
        this->setError(PrinterError::PAPER_JAM);
        return;
    }

    // 正常なら1部印刷
    this->executePrintJob();

    if (this->getRemainingCopies() == 0)
    {
        this->finishPrint();
    }
    else
    {
        this->timer.start(1);
    }
}