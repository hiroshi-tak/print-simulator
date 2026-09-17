cmake_minimum_required(VERSION 3.16)

project(printer-simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(printer
    src/main.cpp

    src/printer/Printer.cpp
    src/printer/PrintJob.cpp

    src/device/PrinterDevice.cpp
    src/device/InkjetPrinter.cpp
    src/device/LaserPrinter.cpp

    src/hardware/Motor.cpp
    src/hardware/Sensor.cpp
    src/hardware/Timer.cpp

    src/logger/Logger.cpp
)

target_include_directories(printer PRIVATE
    src
)

target_link_libraries(printer PRIVATE
    pthread
)

enable_testing()

find_package(GTest REQUIRED)

add_executable(printer_tests
    tests/test_motor.cpp
    tests/test_sensor.cpp
    tests/test_timer.cpp
    tests/test_print_job.cpp
    tests/test_printer.cpp
    tests/test_printer_mock.cpp

    tests/MockPrinterDevice.cpp

    src/printer/Printer.cpp
    src/printer/PrintJob.cpp

    src/device/PrinterDevice.cpp
    src/device/InkjetPrinter.cpp
    src/device/LaserPrinter.cpp

    src/hardware/Motor.cpp
    src/hardware/Sensor.cpp
    src/hardware/Timer.cpp

    src/logger/Logger.cpp
)

target_include_directories(printer_tests PRIVATE
    src
)

target_link_libraries(printer_tests PRIVATE
    GTest::gtest
    GTest::gtest_main
    pthread
)

include(GoogleTest)

gtest_discover_tests(printer_tests)