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
    Printer printer(&inkjet);

    std::cout << "=== 初期状態 ==="
                  << std::endl;

    std::cout << "状態: "
              << stateToString(printer.getState())
              << std::endl;

    std::cout << "エラー: "
              << errorToString(printer.getError())
              << std::endl;

    std::cout << std::endl;

    // =========================
    // 印刷開始
    // =========================

    std::cout << "=== 印刷開始 ==="
              << std::endl;

    printer.startPrint();

    std::cout << "状態: "
              << stateToString(printer.getState())
              << std::endl;

    std::cout << "モーター: "
              << printer.isMotorRunning()
              << std::endl;

    std::cout << "=== 残量確認 ==="
              << std::endl;

    std::cout << "残量: "
              << printer.getRemainingAmount()
              << std::endl;

    std::cout << std::endl;

    // =========================
    // 紙詰まり発生
    // =========================

    std::cout << "=== 紙詰まり発生 ==="
              << std::endl;

    printer.setPaperJamDetected(true);

    std::cout << "状態: "
              << stateToString(printer.getState())
              << std::endl;

    std::cout << "エラー: "
              << errorToString(printer.getError())
              << std::endl;

    std::cout << "モーター: "
              << printer.isMotorRunning()
              << std::endl;

    std::cout << std::endl;

    // =========================
    // エラー解除
    // =========================

    std::cout << "=== エラー解除 ==="
              << std::endl;

    printer.clearError();

    std::cout << "状態: "
              << stateToString(printer.getState())
              << std::endl;

    std::cout << "エラー: "
              << errorToString(printer.getError())
              << std::endl;

    std::cout << "モーター: "
              << printer.isMotorRunning()
              << std::endl;

    std::cout << "=== 印刷による消費 ==="
              << std::endl;

    printer.consumePrintAmount(50);

    std::cout << "残量: "
              << printer.getRemainingAmount()
              << std::endl;

    return 0;
}
