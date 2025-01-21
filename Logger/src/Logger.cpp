#include "Logger.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// Конструктор
Logger::Logger(const std::string& logFileName, LogLevel defaultLevel)
    : logFileName(logFileName), defaultLogLevel(defaultLevel) {
    std::ofstream file(logFileName, std::ios::app); // Открытие файла в режиме добавления
    if (!file) {
        throw std::runtime_error("Couldn't open the log file: " + logFileName);
    }
    file.close();
}

// Метод для изменения уровня важности по умолчанию
void Logger::setDefaultLogLevel(LogLevel level) {
    defaultLogLevel = level;
}

// Метод для записи сообщения в журнал
void Logger::log(const std::string& message, LogLevel level) {
    if (level < defaultLogLevel) {
        return; // Игнорировать сообщения ниже уровня важности
    }

    std::ofstream file(logFileName, std::ios::app); // Открытие файла в режиме добавления
    if (!file) {
        throw std::runtime_error("Couldn't open the log file: " + logFileName);
    }

    // Получение текущего времени
    std::time_t currentTime = std::time(nullptr);
    std::tm timeInfo{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeInfo, &currentTime); // Безопасная версия для Windows
#else
    localtime_r(&currentTime, &timeInfo); // Безопасная версия для POSIX
#endif

    // Форматирование времени
    std::ostringstream timeStream;
    timeStream << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

    // Запись сообщения в файл
    file << "[" << timeStream.str() << "] "
        << "[" << logLevelToString(level) << "] "
        << message << std::endl;
}

// Преобразование уровня важности в строку
std::string Logger::logLevelToString(LogLevel level) const {
    switch (level) {
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}