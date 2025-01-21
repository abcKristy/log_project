# LoggerProject

Проект включает динамическую библиотеку `Logger` для записи сообщений в журнал с различными уровнями важности, а также консольное приложение `LoggerDemo` для демонстрации работы библиотеки.

---

## Описание

**Logger** — это кросс-платформенная динамическая библиотека для записи текстовых сообщений в журнал.  
Журнал хранится в текстовом файле и сохраняет следующую информацию:
- Текст сообщения.
- Уровень важности сообщения (DEBUG, INFO, ERROR).
- Время записи сообщения.

**LoggerDemo** — консольное приложение, которое:
- Использует библиотеку `Logger` для записи сообщений.
- Принимает сообщение и его уровень важности от пользователя.
- Обеспечивает потокобезопасную передачу данных для записи в журнал.

---

## Сборка проекта

### Требования
- **CMake** (минимум 3.10)
- Компилятор C++ с поддержкой стандарта C++17:
  - Windows: Microsoft Visual Studio 2017+.
  - Linux: GCC или Clang.

### Шаги сборки

1. Склонируйте репозиторий:
    
```bash
    git clone <URL репозитория>
    cd LoggerProject
 ```  

2. Создайте папку для сборки:
    
```bash
    mkdir build
    cd build
``` 

3. Выполните генерацию сборочных файлов с помощью CMake:
    
```bash
    cmake ..
```  

4. Соберите проект:
    
```bash
    cmake --build .
```   

После сборки будут созданы:
- `Logger.dll` (Windows) или `libLogger.so` (Linux) — динамическая библиотека.
- `LoggerDemo` — исполняемый файл.

Сборка проекта с Makefile:
    
```bash
    make
```

Это создаст библиотеку libLogger.so в папке build и скомпилирует приложение LoggerDemo.
Прежде чем запустить приложение, нужно указать путь к динамической библиотеке:

```bash
    export LD_LIBRARY_PATH=build:$LD_LIBRARY_PATH./build/LoggerDemo
```

При запуске приложение запросит у пользователя сообщение и уровень важности. Оно будет записывать сообщения в файл log.txt.


---

## Запуск приложения

1. **Параметры запуска:**
   Приложение принимает два параметра командной строки:
   - Имя файла журнала.
   - Уровень важности по умолчанию (`DEBUG`, `INFO`, `ERROR`).

   Пример запуска:
   
```bash
   ./LoggerDemo log.txt INFO
`
```
## Пример работы

Ввод:
```
Введите сообщение: Привет, мир!
Введите уровень важности (DEBUG, INFO, ERROR) [опционально]: INFO
```
Результат в log.txt будет записан в таком виде:
```
2025-01-21 18:45:23 [INFO]: Привет, мир!
```
Для Linux перед запуском добавьте путь к библиотеке в переменную окружения:
```bash
export LD_LIBRARY_PATH=../Logger/build:$LD_LIBRARY_PATH
```

## Структура проекта
```
LoggerProject/
├── Logger/                  # Исходный код библиотеки Logger
│   ├── include/             # Заголовочные файлы
│   │   └── Logger.h
│   ├── src/                 # Реализация библиотеки
│   │   └── Logger.cpp
│   └── CMakeLists.txt       # CMake конфигурация для библиотеки
├── LoggerDemo/              # Исходный код консольного приложения
│   ├── src/
│   │   └── main.cpp         # Точка входа приложения
│   └── CMakeLists.txt       # CMake конфигурация для приложения
├── build/                   # Директория сборки (создается автоматически)
├── CMakeLists.txt           # Главный файл CMake
└── README.md                # Документация
```

Для удобства проверки без запуска проекта на Windows, можно использовать папку build_ready
Для запуска приложения необходимо перейти в дирректорию, где находится LoggerDemo.exe и запустить его с консоли
```bush
cd путь/к/проекту/build_ready/LoggerDemo/Debug
LoggerDemo log.txt INFO
```









