#pragma once

#include "device/PrinterDevice.h"

class MockPrinterDevice : public PrinterDevice
{
public:
    MockPrinterDevice();

    void print() override;
    void print(int copies) override;

    int getRemainingAmount() const override;
    void consumeAmount(int amount) override;

    int getPrintCount() const;

private:
    int remainingAmount;
    int printCount;
};