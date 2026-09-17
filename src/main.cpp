#include <iostream>
#include <thread>
#include <chrono>

#include "printer/Printer.h"
#include "device/InkjetPrinter.h"
#include "device/LaserPrinter.h"
#include "logger/Logger.h"

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

void runPrint(Printer &printer)
{
    printer.startTimer(1);

    while (printer.getRemainingCopies() > 0)
    {
        // 1秒待つ
        std::this_thread::sleep_for(
            std::chrono::seconds(1));

        // タイマー処理
        printer.tickTimer();

        // エラーチェック
        if (printer.getState() == PrinterState::ERROR)
        {
            std::cout << std::endl;
            std::cout << "=== エラー検出 ===" << std::endl;

            std::cout << "エラー: "
                      << errorToString(printer.getError())
                      << std::endl;

            // エラー復旧
            std::cout << "=== エラー復旧 ==="
                      << std::endl;

            printer.setPaperJamDetected(false);
            printer.clearError();

            // 印刷再開
            printer.startPrint();
            printer.startTimer(1);

            continue;
        }

        // 正常時の表示
        std::cout << "1秒経過" << std::endl;

        std::cout << "残り部数: "
                  << printer.getRemainingCopies()
                  << std::endl;

        std::cout << "残量: "
                  << printer.getRemainingAmount()
                  << std::endl;

        std::cout << "状態: "
                  << stateToString(printer.getState())
                  << std::endl;
    }
}

void paperJamInterrupt(Printer &printer)
{
    std::this_thread::sleep_for(
        std::chrono::seconds(3));

    Logger::warning("紙詰まり割り込み発生");

    printer.setPaperJamDetected(true);
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

    std::cout << "残量: "
              << printer.getRemainingAmount()
              << std::endl;

    std::cout << std::endl;

    std::cout << "=== 印刷ジョブ登録 ==="
              << std::endl;

    printer.createPrintJob(5);

    std::cout << "総部数: "
              << printer.getTotalCopies()
              << std::endl;

    std::cout << "残り部数: "
              << printer.getRemainingCopies()
              << std::endl;

    std::cout << std::endl;

    std::cout << "=== 印刷開始 ==="
              << std::endl;

    printer.startPrint();

    std::cout << "状態: "
              << stateToString(printer.getState())
              << std::endl;
    
    std::cout << "モーター: "
              << printer.isMotorRunning()
              << std::endl;

    std::thread jamThread(
        paperJamInterrupt,
        std::ref(printer));

    runPrint(printer);

    jamThread.join();

    return 0;
}