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

    case PrinterState::ERROR:
        return "ERROR";
    }

    return "UNKNOWN";
}

const char *errorToString(PrinterError error)
{
    switch (error)
    {
    case PrinterError::NONE:
        return "NONE";

    case PrinterError::PAPER_JAM:
        return "PAPER_JAM";

    case PrinterError::NO_PAPER:
        return "NO_PAPER";

    case PrinterError::INK_EMPTY:
        return "INK_EMPTY";
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

    std::cout << std::endl;

    std::cout << "=== エラー発生 ==="
              << std::endl;

    inkjetPrinter.setError(PrinterError::PAPER_JAM);

    std::cout << "状態: "
              << stateToString(inkjetPrinter.getState())
              << std::endl;

    std::cout << "エラー: "
              << errorToString(inkjetPrinter.getError())
              << std::endl;

    std::cout << "モーター: "
              << inkjetPrinter.isMotorRunning()
              << std::endl;

    inkjetPrinter.clearError();

    std::cout << "エラー解除後: "
              << stateToString(inkjetPrinter.getState())
              << std::endl;

    std::cout << "エラー: "
              << errorToString(inkjetPrinter.getError())
              << std::endl;

    return 0;
}