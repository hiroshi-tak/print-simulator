#include <gtest/gtest.h>

#include "hardware/Sensor.h"

TEST(SensorTest, InitialPaperIsDetected)
{
    Sensor sensor;

    EXPECT_TRUE(sensor.isPaperDetected());
}

TEST(SensorTest, PaperCanBeRemoved)
{
    Sensor sensor;

    sensor.setPaperDetected(false);

    EXPECT_FALSE(sensor.isPaperDetected());
}

TEST(SensorTest, PaperCanBeDetected)
{
    Sensor sensor;

    sensor.setPaperDetected(false);
    sensor.setPaperDetected(true);

    EXPECT_TRUE(sensor.isPaperDetected());
}

TEST(SensorTest, InitialPaperJamIsNotDetected)
{
    Sensor sensor;

    EXPECT_FALSE(sensor.isPaperJamDetected());
}

TEST(SensorTest, PaperJamCanBeDetected)
{
    Sensor sensor;

    sensor.setPaperJamDetected(true);

    EXPECT_TRUE(sensor.isPaperJamDetected());
}

TEST(SensorTest, PaperJamCanBeCleared)
{
    Sensor sensor;

    sensor.setPaperJamDetected(true);
    sensor.setPaperJamDetected(false);

    EXPECT_FALSE(sensor.isPaperJamDetected());
}