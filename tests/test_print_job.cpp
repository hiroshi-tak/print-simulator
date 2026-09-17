#include <gtest/gtest.h>

#include "printer/PrintJob.h"

TEST(PrintJobTest, InitialStateHasNoJob)
{
    PrintJob job;

    EXPECT_FALSE(job.hasJob());
    EXPECT_EQ(job.getTotalCopies(), 0);
    EXPECT_EQ(job.getRemainingCopies(), 0);
}

TEST(PrintJobTest, CreateJob)
{
    PrintJob job;

    job.create(5);

    EXPECT_TRUE(job.hasJob());
    EXPECT_EQ(job.getTotalCopies(), 5);
    EXPECT_EQ(job.getRemainingCopies(), 5);
}

TEST(PrintJobTest, PrintOneCopy)
{
    PrintJob job;

    job.create(5);

    EXPECT_TRUE(job.printOne());

    EXPECT_EQ(job.getRemainingCopies(), 4);
}

TEST(PrintJobTest, PrintAllCopies)
{
    PrintJob job;

    job.create(3);

    EXPECT_TRUE(job.printOne());
    EXPECT_TRUE(job.printOne());
    EXPECT_TRUE(job.printOne());

    EXPECT_EQ(job.getRemainingCopies(), 0);
    EXPECT_FALSE(job.hasJob());
}

TEST(PrintJobTest, CannotPrintWhenNoCopiesRemain)
{
    PrintJob job;

    job.create(1);

    EXPECT_TRUE(job.printOne());
    EXPECT_FALSE(job.printOne());

    EXPECT_EQ(job.getRemainingCopies(), 0);
}

TEST(PrintJobTest, InvalidCopiesAreIgnored)
{
    PrintJob job;

    job.create(0);

    EXPECT_FALSE(job.hasJob());
    EXPECT_EQ(job.getTotalCopies(), 0);
    EXPECT_EQ(job.getRemainingCopies(), 0);
}