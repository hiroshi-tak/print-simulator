#include <gtest/gtest.h>

#include "hardware/Timer.h"

TEST(TimerTest, InitialStateIsNotExpired)
{
    Timer timer;

    EXPECT_FALSE(timer.isExpired());
}

TEST(TimerTest, TimerExpiresAfterTicks)
{
    Timer timer;

    timer.start(3);

    EXPECT_FALSE(timer.isExpired());

    timer.tick();
    EXPECT_FALSE(timer.isExpired());

    timer.tick();
    EXPECT_FALSE(timer.isExpired());

    timer.tick();
    EXPECT_TRUE(timer.isExpired());
}

TEST(TimerTest, StopTimer)
{
    Timer timer;

    timer.start(3);
    timer.stop();

    EXPECT_FALSE(timer.isExpired());
}

TEST(TimerTest, RestartTimer)
{
    Timer timer;

    timer.start(3);

    timer.tick();
    timer.tick();

    timer.start(2);

    EXPECT_FALSE(timer.isExpired());

    timer.tick();
    EXPECT_FALSE(timer.isExpired());

    timer.tick();
    EXPECT_TRUE(timer.isExpired());
}