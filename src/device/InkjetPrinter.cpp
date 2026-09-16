#include <iostream>
#include "InkjetPrinter.h"

InkjetPrinter::InkjetPrinter()
{
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