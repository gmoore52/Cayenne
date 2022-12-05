cmake_minimum_required(VERSION 3.22)
project(EngineGamePractice)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(EngineName)

target_link_libraries(${PROJECT_NAME} PUBLIC EngineName)

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/EngineName"
                           )

