#include <gtest/gtest.h>

#include "printer/Printer.h"
#include "device/InkjetPrinter.h"

TEST(PrinterTest, InitialStateIsIdle)
{
    InkjetPrinter device;
    Printer printer(&device);

    EXPECT_EQ(printer.getState(), PrinterState::IDLE);
}

TEST(PrinterTest, StartPrint)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.setPaperDetected(true);

    printer.startPrint();

    EXPECT_EQ(printer.getState(), PrinterState::PRINTING);
    EXPECT_TRUE(printer.isMotorRunning());
}

TEST(PrinterTest, CannotStartPrintWithoutPaper)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.setPaperDetected(false);

    printer.startPrint();

    EXPECT_EQ(printer.getState(), PrinterState::IDLE);
    EXPECT_FALSE(printer.isMotorRunning());
}

TEST(PrinterTest, StopPrint)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.startPrint();
    printer.stopPrint();

    EXPECT_EQ(printer.getState(), PrinterState::STOPPED);
    EXPECT_FALSE(printer.isMotorRunning());
}

TEST(PrinterTest, FinishPrint)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.startPrint();
    printer.finishPrint();

    EXPECT_EQ(printer.getState(), PrinterState::IDLE);
    EXPECT_FALSE(printer.isMotorRunning());
}

TEST(PrinterTest, PaperJamCausesError)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.startPrint();

    printer.setPaperJamDetected(true);

    printer.startTimer(1);
    printer.tickTimer();

    EXPECT_EQ(printer.getState(), PrinterState::ERROR);
    EXPECT_EQ(printer.getError(), PrinterError::PAPER_JAM);
    EXPECT_FALSE(printer.isMotorRunning());
}

TEST(PrinterTest, ClearError)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.setError(PrinterError::PAPER_JAM);

    EXPECT_EQ(printer.getState(), PrinterState::ERROR);
    EXPECT_EQ(printer.getError(), PrinterError::PAPER_JAM);

    printer.clearError();

    EXPECT_EQ(printer.getState(), PrinterState::IDLE);
    EXPECT_EQ(printer.getError(), PrinterError::NONE);
}

TEST(PrinterTest, CreatePrintJob)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.createPrintJob(5);

    EXPECT_EQ(printer.getTotalCopies(), 5);
    EXPECT_EQ(printer.getRemainingCopies(), 5);
}

TEST(PrinterTest, ExecuteOnePrintJob)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.createPrintJob(5);
    printer.startPrint();

    EXPECT_TRUE(printer.executePrintJob());

    EXPECT_EQ(printer.getRemainingCopies(), 4);
    EXPECT_EQ(printer.getRemainingAmount(), 99);
}

TEST(PrinterTest, ExecuteAllPrintJobs)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.createPrintJob(3);
    printer.startPrint();

    EXPECT_TRUE(printer.executePrintJob());
    EXPECT_TRUE(printer.executePrintJob());
    EXPECT_TRUE(printer.executePrintJob());

    EXPECT_EQ(printer.getRemainingCopies(), 0);
    EXPECT_EQ(printer.getRemainingAmount(), 97);
}

TEST(PrinterTest, CannotExecutePrintJobWhenPrinterIsIdle)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.createPrintJob(3);

    EXPECT_FALSE(printer.executePrintJob());

    EXPECT_EQ(printer.getRemainingCopies(), 3);
}

TEST(PrinterTest, InkEmptyCausesError)
{
    InkjetPrinter device;
    Printer printer(&device);

    printer.createPrintJob(101);
    printer.startPrint();

    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(printer.executePrintJob());
    }

    EXPECT_EQ(printer.getRemainingAmount(), 0);

    EXPECT_FALSE(printer.executePrintJob());

    EXPECT_EQ(printer.getState(), PrinterState::ERROR);
    EXPECT_EQ(printer.getError(), PrinterError::INK_EMPTY);
}