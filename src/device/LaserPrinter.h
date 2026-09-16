#pragma once

#include "PrinterDevice.h"

class LaserPrinter : public PrinterDevice
{
public:
    LaserPrinter();

    void print() override;
    void print(int copies) override;
};