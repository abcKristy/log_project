# Создание динамической библиотеки Logger
add_library(Logger SHARED
    src/Logger.cpp
    include/Logger.h
)

# Указание директорий для заголовочных файлов
target_include_directories(Logger PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Настройка вывода для DLL и LIB
set_target_properties(Logger PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Logger/Debug"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Logger/Debug"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Logger/Debug"
)

# Определение макроса для экспорта функций
target_compile_definitions(Logger PRIVATE LOGGER_EXPORTS)