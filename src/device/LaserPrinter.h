#pragma once

#include "PrinterDevice.h"

class LaserPrinter : public PrinterDevice
{
public:
    LaserPrinter();

    void print() override;
    void print(int copies) override;

    int getRemainingAmount() const override;
    void consumeAmount(int amount) override;

private:
    int tonerAmount;
};