#pragma once

#include "PrinterDevice.h"

class InkjetPrinter : public PrinterDevice
{
public:
    InkjetPrinter();

    void print() override;
    void print(int copies) override;
};