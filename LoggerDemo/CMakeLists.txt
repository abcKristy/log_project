cmake_minimum_required(VERSION 3.10)
project(LoggerDemo)

# Указываем, где искать файлы заголовков
include_directories(${CMAKE_SOURCE_DIR}/Logger/include)

# Добавляем исполняемый файл
add_executable(LoggerDemo src/main.cpp)

# Подключаем динамическую библиотеку Logger
target_link_libraries(LoggerDemo Logger)