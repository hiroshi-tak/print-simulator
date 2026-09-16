#pragma once

class PrinterDevice
{
public:
    PrinterDevice();

    virtual ~PrinterDevice();

    virtual void print() = 0;
    virtual void print(int copies) = 0;

    virtual int getRemainingAmount() const = 0;
    virtual void consumeAmount(int amount) = 0;
};