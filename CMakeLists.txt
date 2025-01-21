cmake_minimum_required(VERSION 3.15)
project(LoggerProject)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление подкаталогов
add_subdirectory(Logger)
add_subdirectory(LoggerDemo)