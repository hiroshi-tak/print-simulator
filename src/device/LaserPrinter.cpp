#include <iostream>
#include "LaserPrinter.h"

LaserPrinter::LaserPrinter()
{
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