project(Cayenne)
set(CayenneBuildStatic TRUE)
# Set and check if library is built in static mode
if(CayenneBuildStatic)
    add_definitions(-DCAYENNE_BUILD_STATIC)
    set(BUILD_CONFIGURATION STATIC)
else()
    set(BUILD_MODE_DEFINITIONS -DCY_BUILD_DLL)
    set(BUILD_CONFIGURATION SHARED)
endif(CayenneBuildStatic)

set(BUILD_CONFIGURATION STATIC)

# Handle different configurations, setup debug and relase configs on your own to define these variables
if(CMAKE_BUILD_TYPE EQUAL "Debug")
    add_definitions(-DCY_ENABLE_ASSERTS)
elseif(CMAKE_BUILD_TYPE EQUAL "Release")
endif()


if(WIN32)
    add_definitions(-DCY_PLATFORM_WINDOWS
                    ${BUILD_MODE_DEFINITIONS})
    set(PLATFORM_FILES ${PROJECT_SOURCE_DIR}/platform/Win32/Win32Window.cpp
                       ${PROJECT_SOURCE_DIR}/platform/Win32/Win32Input.cpp
                       )
    set(PLATFORM_RENDER ${PROJECT_SOURCE_DIR}/platform/OpenGL/OpenGLContext.cpp
                        ${PROJECT_SOURCE_DIR}/platform/OpenGL/OpenGLBuffer.cpp
                        platform/OpenGL/OpenGLVertexArray.cpp
                        platform/OpenGL/OpenGLVertexArray.h
                        platform/OpenGL/OpenGLRenderAPI.cpp
                        platform/OpenGL/OpenGLRenderAPI.h
                        platform/OpenGL/OpenGLShader.cpp
                        platform/OpenGL/OpenGLShader.h
                        platform/OpenGL/OpenGLTexture.cpp
                        platform/OpenGL/OpenGLTexture.h)
endif(WIN32)

set(RENDER_FILES ${PROJECT_SOURCE_DIR}/src/Engine/renderer/Renderer.cpp
                 ${PROJECT_SOURCE_DIR}/src/Engine/renderer/Shader.cpp
                 ${PROJECT_SOURCE_DIR}/src/Engine/renderer/Buffer.cpp
                 ${PLATFORM_RENDER}
                 src/Engine/renderer/VertexArray.cpp
                 src/Engine/renderer/VertexArray.h
                 src/Engine/renderer/OrthographicCamera.cpp
                 src/Engine/renderer/OrthographicCamera.h
                 src/Engine/renderer/Texture.cpp
                 src/Engine/renderer/Texture.h
                 src/Engine/renderer/Renderer2.cpp
                 src/Engine/renderer/Renderer2.h)

set(ECS_FILES src/Engine/ECS/Entity.h
              src/Engine/ECS/Component.h
              src/Engine/ECS/System.h
              src/Engine/ECS/EntityManager.h
              src/Engine/ECS/EntityManager.cpp
              src/Engine/ECS/ComponentManager.h
              src/Engine/ECS/SystemManager.h
              src/Engine/ECS/ECS.h
              src/Engine/ECS/ECS.cpp
        )

set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/Engine/Core/Layer.cpp
                 ${PROJECT_SOURCE_DIR}/src/Engine/Core/LayerStack.cpp
                 ${PROJECT_SOURCE_DIR}/src/Engine/Core/Log.cpp
                 ${PROJECT_SOURCE_DIR}/src/Engine/Core/Application.cpp
                 ${PROJECT_SOURCE_DIR}/src/ImGui/ImGuiLayer.cpp
                 ${PROJECT_SOURCE_DIR}/src/Cayenne.h
                 src/Engine/Core/Timestep.h
                 src/Engine/Core/CameraController.cpp
                 src/Engine/Core/CameraController.h)

add_subdirectory(lib/spdlog)

add_subdirectory(lib/GLAD)

add_subdirectory(lib/GLFW)

add_subdirectory(lib/GLM)

add_subdirectory(lib/ImGui)

find_package(spdlog)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/lib/spdlog/include)


add_library(${PROJECT_NAME} ${BUILD_CONFIGURATION}
                            ${PROJECT_SOURCE_DIR}/src/cayennepch.h
                            ${PLATFORM_FILES}
                            ${RENDER_FILES}
                            ${ECS_FILES}
                            ${SOURCE_FILES}
                            )

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glfw glad glm ImGui libopengl32.a)
#target_precompile_headers(${PROJECT_NAME} PUBLIC src/cayennepch.h)


