#include <iostream>

#include "printer/Printer.h"
#include "device/InkjetPrinter.h"
#include "device/LaserPrinter.h"

const char *stateToString(PrinterState state)
{
    switch (state)
    {
    case PrinterState::IDLE:
        return "IDLE";

    case PrinterState::PRINTING:
        return "PRINTING";

    case PrinterState::STOPPED:
        return "STOPPED";
    }

    return "UNKNOWN";
}

int main()
{
    InkjetPrinter inkjet;
    Printer inkjetPrinter(&inkjet);

    std::cout << "=== インクジェットプリンター ==="
              << std::endl;

    std::cout << "初期状態: "
              << stateToString(inkjetPrinter.getState())
              << std::endl;

    inkjetPrinter.startPrint();

    std::cout << "印刷状態: "
              << stateToString(inkjetPrinter.getState())
              << std::endl;

    std::cout << "モーター: "
              << inkjetPrinter.isMotorRunning()
              << std::endl;

    inkjetPrinter.finishPrint();

    std::cout << "印刷完了後: "
              << stateToString(inkjetPrinter.getState())
              << std::endl;

    std::cout << std::endl;

    LaserPrinter laser;
    Printer laserPrinter(&laser);

    std::cout << "=== レーザープリンター ==="
              << std::endl;

    laserPrinter.startPrint();

    std::cout << "印刷状態: "
              << stateToString(laserPrinter.getState())
              << std::endl;

    std::cout << "モーター: "
              << laserPrinter.isMotorRunning()
              << std::endl;

    laserPrinter.finishPrint();

    std::cout << "印刷完了後: "
              << stateToString(laserPrinter.getState())
              << std::endl;

    return 0;
}