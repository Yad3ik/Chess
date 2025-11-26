cmake_minimum_required(VERSION 3.16)

project(Chess LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Доп. флаги (asan и отладка)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-g -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

# Исполняемый файл
add_executable(chess
    src/main.cpp
    src/chessboard.cpp
)

# Путь к заголовкам
target_include_directories(chess PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)