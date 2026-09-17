#include <iostream>
#include "Logger.h"

void Logger::info(const std::string &message)
{
    std::cout << "[INFO] "
              << message
              << std::endl;
}

void Logger::warning(const std::string &message)
{
    std::cout << "[WARNING] "
              << message
              << std::endl;
}

void Logger::error(const std::string &message)
{
    std::cout << "[ERROR] "
              << message
              << std::endl;
}