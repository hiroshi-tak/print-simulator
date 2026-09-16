#pragma once

class PrinterDevice
{
public:
    PrinterDevice();

    virtual ~PrinterDevice();

    virtual void print() = 0;
    virtual void print(int copies) = 0;
};