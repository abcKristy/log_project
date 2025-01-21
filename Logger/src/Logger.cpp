#include "Logger.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// �����������
Logger::Logger(const std::string& logFileName, LogLevel defaultLevel)
    : logFileName(logFileName), defaultLogLevel(defaultLevel) {
    std::ofstream file(logFileName, std::ios::app); // �������� ����� � ������ ����������
    if (!file) {
        throw std::runtime_error("Couldn't open the log file: " + logFileName);
    }
    file.close();
}

// ����� ��� ��������� ������ �������� �� ���������
void Logger::setDefaultLogLevel(LogLevel level) {
    defaultLogLevel = level;
}

// ����� ��� ������ ��������� � ������
void Logger::log(const std::string& message, LogLevel level) {
    if (level < defaultLogLevel) {
        return; // ������������ ��������� ���� ������ ��������
    }

    std::ofstream file(logFileName, std::ios::app); // �������� ����� � ������ ����������
    if (!file) {
        throw std::runtime_error("Couldn't open the log file: " + logFileName);
    }

    // ��������� �������� �������
    std::time_t currentTime = std::time(nullptr);
    std::tm timeInfo{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeInfo, &currentTime); // ���������� ������ ��� Windows
#else
    localtime_r(&currentTime, &timeInfo); // ���������� ������ ��� POSIX
#endif

    // �������������� �������
    std::ostringstream timeStream;
    timeStream << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

    // ������ ��������� � ����
    file << "[" << timeStream.str() << "] "
        << "[" << logLevelToString(level) << "] "
        << message << std::endl;
}

// �������������� ������ �������� � ������
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