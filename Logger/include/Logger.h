#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// ������� ������� ��� Windows DLL
#if defined(_WIN32) || defined(_WIN64)
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport) // ������� ��� ������ DLL
#else
#define LOGGER_API __declspec(dllimport) // ������ ��� ������������� DLL
#endif
#else
#define LOGGER_API
#endif

// ������������ ������� �������� ���������
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

// ����� ��� ������ � ��������
class LOGGER_API Logger {
public:
    Logger(const std::string& logFileName, LogLevel defaultLevel);
    void setDefaultLogLevel(LogLevel level);
    void log(const std::string& message, LogLevel level);

private:
    std::string logFileName;    // ��� ����� �������
    LogLevel defaultLogLevel;   // ������� �������� �� ���������

    std::string logLevelToString(LogLevel level) const;
};

#endif // LOGGER_H