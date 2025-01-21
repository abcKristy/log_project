#ifndef LOGGER_H
#define LOGGER_H

#include <string>

// Ёкспорт функций дл€ Windows DLL
#if defined(_WIN32) || defined(_WIN64)
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport) // Ёкспорт дл€ сборки DLL
#else
#define LOGGER_API __declspec(dllimport) // »мпорт дл€ использовани€ DLL
#endif
#else
#define LOGGER_API
#endif

// ѕеречисление уровней важности сообщений
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

//  ласс дл€ работы с журналом
class LOGGER_API Logger {
public:
    Logger(const std::string& logFileName, LogLevel defaultLevel);
    void setDefaultLogLevel(LogLevel level);
    void log(const std::string& message, LogLevel level);

private:
    std::string logFileName;    // »м€ файла журнала
    LogLevel defaultLogLevel;   // ”ровень важности по умолчанию

    std::string logLevelToString(LogLevel level) const;
};

#endif // LOGGER_H