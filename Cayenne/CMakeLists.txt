project(Cayenne)
if(WIN32)
    add_definitions(-DCY_PLATFORM_WINDOWS
                    -DCY_BUILD_DLL)
endif(WIN32)

add_subdirectory(lib/spdlog)

add_subdirectory(lib/GLAD)
add_subdirectory(lib/GLFW)


add_subdirectory(lib/ImGui)

find_package(spdlog)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/lib/spdlog/include)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR}/src/cayennepch.h
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Window.h
                                   ${PROJECT_SOURCE_DIR}/platform/Win32/Win32Window.cpp
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Layer.cpp
                                   ${PROJECT_SOURCE_DIR}/src/Engine/LayerStack.cpp
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Log.cpp
                                   ${PROJECT_SOURCE_DIR}/src/Engine/Application.cpp
                                   ${PROJECT_SOURCE_DIR}/src/ImGui/ImGuiLayer.cpp
                                   )

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glfw glad ImGui libopengl32.a)
#target_precompile_headers(${PROJECT_NAME} PUBLIC src/cayennepch.h)


