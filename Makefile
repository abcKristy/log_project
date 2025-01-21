# ���������� � �����
CC = gcc
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -pthread

# �����
SRC_DIR = .
BUILD_DIR = build
LOGGER_DIR = Logger
LOGGER_DEMO_DIR = LoggerDemo

# �����
LOGGER_SRC = $(LOGGER_DIR)/src/Logger.cpp
LOGGER_HDR = $(LOGGER_DIR)/include/Logger.h
LOGGER_LIB = $(BUILD_DIR)/libLogger.so

LOGGER_DEMO_SRC = $(LOGGER_DEMO_DIR)/src/main.cpp
LOGGER_DEMO = $(BUILD_DIR)/LoggerDemo

# ���� ������
all: $(LOGGER_LIB) $(LOGGER_DEMO)

# ������ ������������ ���������� Logger
$(LOGGER_LIB): $(LOGGER_SRC) $(LOGGER_HDR)
 mkdir -p $(BUILD_DIR)
 $(CXX) $(CXXFLAGS) -fPIC -shared -o $@ $(LOGGER_SRC)

# ������ ����������� ���������� LoggerDemo
$(LOGGER_DEMO): $(LOGGER_DEMO_SRC) $(LOGGER_LIB)
 mkdir -p $(BUILD_DIR)
 $(CXX) $(CXXFLAGS) -o $@ $(LOGGER_DEMO_SRC) -L$(BUILD_DIR) -lLogger $(LDFLAGS)

# ������� ��������� ������
clean:
 rm -rf $(BUILD_DIR)

# �������� �����
.PHONY: all clean