#include <iostream>
#include "LaserPrinter.h"

LaserPrinter::LaserPrinter()
{
    this->tonerAmount = 100;
}

void LaserPrinter::print()
{
    std::cout << "レーザー方式で印刷します"
              << std::endl;
}

void LaserPrinter::print(int copies)
{
    std::cout << "レーザー方式で"
              << copies
              << "部印刷します"
              << std::endl;
}

int LaserPrinter::getRemainingAmount() const
{
    return this->tonerAmount;
}

void LaserPrinter::consumeAmount(int amount)
{
    this->tonerAmount -= amount;

    if (this->tonerAmount < 0)
    {
        this->tonerAmount = 0;
    }
}