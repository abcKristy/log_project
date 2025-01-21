# Компилятор и флаги
CC = gcc
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -pthread

# Папки
SRC_DIR = .
BUILD_DIR = build
LOGGER_DIR = Logger
LOGGER_DEMO_DIR = LoggerDemo

# Файлы
LOGGER_SRC = $(LOGGER_DIR)/src/Logger.cpp
LOGGER_HDR = $(LOGGER_DIR)/include/Logger.h
LOGGER_LIB = $(BUILD_DIR)/libLogger.so

LOGGER_DEMO_SRC = $(LOGGER_DEMO_DIR)/src/main.cpp
LOGGER_DEMO = $(BUILD_DIR)/LoggerDemo

# Цели сборки
all: $(LOGGER_LIB) $(LOGGER_DEMO)

# Сборка динамической библиотеки Logger
$(LOGGER_LIB): $(LOGGER_SRC) $(LOGGER_HDR)
 mkdir -p $(BUILD_DIR)
 $(CXX) $(CXXFLAGS) -fPIC -shared -o $@ $(LOGGER_SRC)

# Сборка консольного приложения LoggerDemo
$(LOGGER_DEMO): $(LOGGER_DEMO_SRC) $(LOGGER_LIB)
 mkdir -p $(BUILD_DIR)
 $(CXX) $(CXXFLAGS) -o $@ $(LOGGER_DEMO_SRC) -L$(BUILD_DIR) -lLogger $(LDFLAGS)

# Очистка временных файлов
clean:
 rm -rf $(BUILD_DIR)

# Указание целей
.PHONY: all clean