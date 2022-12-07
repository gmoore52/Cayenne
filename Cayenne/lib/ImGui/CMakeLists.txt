project(ImGui)

include_directories(../GLFW/include)

set(PLATFORM_LIBS ../../platform/Win32/imgui_impl_opengl3.cpp
                  ../../platform/Win32/imgui_impl_glfw.cpp)

add_library(${PROJECT_NAME} STATIC imgui/imconfig.h
                                   imgui/imgui.h
                                   imgui/imgui.cpp
                                   imgui/imgui_draw.cpp
                                   imgui/imgui_internal.h
                                   imgui/imgui_widgets.cpp
                                   imgui/imgui_tables.cpp
                                   imgui/imstb_rectpack.h
                                   imgui/imstb_textedit.h
                                   imgui/imstb_truetype.h
                                   imgui/imgui_demo.cpp
                                   ${PLATFORM_LIBS})