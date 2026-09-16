#pragma once

#include "PrinterDevice.h"

class InkjetPrinter : public PrinterDevice
{
public:
    InkjetPrinter();

    void print() override;
    void print(int copies) override;

    int getRemainingAmount() const override;
    void consumeAmount(int amount) override;

private:
    int inkAmount;
};