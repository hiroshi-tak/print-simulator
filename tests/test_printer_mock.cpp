#include <gtest/gtest.h>

#include "printer/Printer.h"
#include "MockPrinterDevice.h"

TEST(PrinterMockTest, PrinterCanPrintUsingMockDevice)
{
    MockPrinterDevice device;
    Printer printer(&device);

    printer.createPrintJob(3);
    printer.startPrint();

    EXPECT_TRUE(printer.executePrintJob());

    EXPECT_EQ(device.getPrintCount(), 1);
    EXPECT_EQ(device.getRemainingAmount(), 99);
    EXPECT_EQ(printer.getRemainingCopies(), 2);
}

TEST(PrinterMockTest, PrinterCanPrintMultipleCopies)
{
    MockPrinterDevice device;
    Printer printer(&device);

    printer.createPrintJob(3);
    printer.startPrint();

    EXPECT_TRUE(printer.executePrintJob());
    EXPECT_TRUE(printer.executePrintJob());
    EXPECT_TRUE(printer.executePrintJob());

    EXPECT_EQ(device.getPrintCount(), 3);
    EXPECT_EQ(device.getRemainingAmount(), 97);
    EXPECT_EQ(printer.getRemainingCopies(), 0);
}

TEST(PrinterMockTest, PrinterStopsWhenDeviceAmountIsEmpty)
{
    MockPrinterDevice device;
    Printer printer(&device);

    printer.createPrintJob(101);
    printer.startPrint();

    for (int i = 0; i < 100; i++)
    {
        EXPECT_TRUE(printer.executePrintJob());
    }

    EXPECT_EQ(device.getRemainingAmount(), 0);
    EXPECT_EQ(device.getPrintCount(), 100);

    EXPECT_FALSE(printer.executePrintJob());

    EXPECT_EQ(printer.getState(), PrinterState::ERROR);
    EXPECT_EQ(printer.getError(), PrinterError::INK_EMPTY);
}