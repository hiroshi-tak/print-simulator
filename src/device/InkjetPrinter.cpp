#include <iostream>
#include "InkjetPrinter.h"

InkjetPrinter::InkjetPrinter()
{
    this->inkAmount = 100;
}

void InkjetPrinter::print()
{
    std::cout << "インクジェット方式で印刷します"
              << std::endl;
}

void InkjetPrinter::print(int copies)
{
    std::cout << "インクジェット方式で"
              << copies
              << "部印刷します"
              << std::endl;
}

int InkjetPrinter::getRemainingAmount() const
{
    return this->inkAmount;
}

void InkjetPrinter::consumeAmount(int amount)
{
    this->inkAmount -= amount;

    if (this->inkAmount < 0)
    {
        this->inkAmount = 0;
    }
}