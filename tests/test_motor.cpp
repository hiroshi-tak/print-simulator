#include <gtest/gtest.h>

#include "hardware/Motor.h"

TEST(MotorTest, InitialStateIsStopped)
{
    Motor motor;

    EXPECT_FALSE(motor.isRunning());
}

TEST(MotorTest, StartMotor)
{
    Motor motor;

    motor.start();

    EXPECT_TRUE(motor.isRunning());
}

TEST(MotorTest, StopMotor)
{
    Motor motor;

    motor.start();
    motor.stop();

    EXPECT_FALSE(motor.isRunning());
}