cmake_minimum_required(VERSION 3.22)
project(CayenneTestProject)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif(UNIX AND NOT APPLE)

if(WIN32)
    add_definitions(-DCY_PLATFORM_WINDOWS
                    -DCAYENNE_BUILD_STATIC)
elseif(LINUX)
    add_definitions(-DCY_PLATFORM_LINUX
                    -DCAYENNE_BUILD_STATIC)
endif(WIN32)


set(CMAKE_CXX_STANDARD 23)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCY_ENABLE_ASSERTS)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
endif()

add_subdirectory(Cayenne)
# Build exe in to the TestApp folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../TestApp/)
add_executable(${PROJECT_NAME} TestApp/Test.cpp TestApp/TestApplicationLayer.cpp TestApp/TestApplicationLayer.h)

target_link_libraries(${PROJECT_NAME} PUBLIC Cayenne)

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/Cayenne/src
                           )

#target_precompile_headers(${PROJECT_NAME} PUBLIC Cayenne/src/cayennepch.h)

#add_custom_command(
#            TARGET ${PROJECT_NAME} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_directory
#            $<TARGET_FILE_DIR:Cayenne>
#            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
