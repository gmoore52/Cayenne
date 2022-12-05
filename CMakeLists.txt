cmake_minimum_required(VERSION 3.22)
project(CayenneTestProject)

if(WIN32)
    add_definitions(-DCY_PLATFORM_WINDOWS)
endif(WIN32)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} TestApp/Test.cpp)

add_subdirectory(Cayenne)

target_link_libraries(${PROJECT_NAME} PUBLIC Cayenne)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/Cayenne/src
                           )

#target_precompile_headers(${PROJECT_NAME} PUBLIC Cayenne/src/cayennepch.h)

add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            $<TARGET_FILE_DIR:Cayenne>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
