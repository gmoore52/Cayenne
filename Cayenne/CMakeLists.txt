project(Cayenne)
if(WIN32)
    add_definitions(-DCY_PLATFORM_WINDOWS
                    -DCY_BUILD_DLL)
endif(WIN32)

add_subdirectory(lib/spdlog)

find_package(spdlog)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/lib/spdlog/include)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR}/src/cayennepch.h
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Application.cpp
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Log.cpp)

target_link_libraries(${PROJECT_NAME} spdlog)
#target_precompile_headers(${PROJECT_NAME} PUBLIC src/cayennepch.h)


