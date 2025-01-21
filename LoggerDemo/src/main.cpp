#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include "Logger.h"

// ������� ��� ���������
std::queue<std::pair<std::string, LogLevel>> messageQueue;
std::mutex queueMutex;
std::condition_variable condition;
bool done = false; // ���� ���������� ������

// ������� ��������� ��������� � ��������� ������
void processMessages(Logger& logger) {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        condition.wait(lock, [] { return !messageQueue.empty() || done; });

        while (!messageQueue.empty()) {
            auto messagePair = messageQueue.front();
            messageQueue.pop();
            lock.unlock();

            // ���������� ��������� � ������
            logger.log(messagePair.first, messagePair.second);

            lock.lock();
        }

        if (done) break;
    }
}

int main(int argc, char* argv[]) {
    // ��������� ��������� ��������� ������
    if (argc < 3) {
        std::cerr << "Usage: LoggerDemo <log file_name> <level of importance>" << std::endl;
        return 1;
    }

    // ������������� ����������
    std::string logFileName = argv[1];
    LogLevel defaultLogLevel;

    // ���������� ������� �������� �� ���������
    std::string levelStr = argv[2];
    if (levelStr == "INFO") {
        defaultLogLevel = LogLevel::INFO;
    }
    else if (levelStr == "WARNING") {
        defaultLogLevel = LogLevel::WARNING;
    }
    else if (levelStr == "ERROR") {
        defaultLogLevel = LogLevel::ERROR;
    }
    else {
        std::cerr << "Unacceptable level of importance: " << levelStr << std::endl;
        return 1;
    }

    // ������� ������ Logger
    Logger logger(logFileName, defaultLogLevel);

    // ��������� ����� ��������� ���������
    std::thread processorThread(processMessages, std::ref(logger));

    // ���� ������ �������������
    std::cout << "Enter the message and the importance level (INFO, WARNING, ERROR):" << std::endl;

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            // ���������� ����� �� ��������� ������
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                done = true;
            }
            condition.notify_one();
            break;
        }

        // ��������� ��������� � ������� ��������
        size_t pos = input.find_last_of(" ");
        std::string message = input;
        LogLevel level = defaultLogLevel;

        if (pos != std::string::npos) {
            std::string levelInput = input.substr(pos + 1);
            message = input.substr(0, pos);

            if (levelInput == "INFO") {
                level = LogLevel::INFO;
            }
            else if (levelInput == "WARNING") {
                level = LogLevel::WARNING;
            }
            else if (levelInput == "ERROR") {
                level = LogLevel::ERROR;
            }
        }

        // ��������� ��������� � �������
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.emplace(message, level);
        }
        condition.notify_one();
    }

    // ������� ���������� ������
    processorThread.join();
    return 0;
}