#include "MockPrinterDevice.h"

MockPrinterDevice::MockPrinterDevice()
{
    this->remainingAmount = 100;
    this->printCount = 0;
}

void MockPrinterDevice::print()
{
    this->printCount++;
}

void MockPrinterDevice::print(int copies)
{
    this->printCount += copies;
}

int MockPrinterDevice::getRemainingAmount() const
{
    return this->remainingAmount;
}

void MockPrinterDevice::consumeAmount(int amount)
{
    this->remainingAmount -= amount;

    if (this->remainingAmount < 0)
    {
        this->remainingAmount = 0;
    }
}

int MockPrinterDevice::getPrintCount() const
{
    return this->printCount;
}