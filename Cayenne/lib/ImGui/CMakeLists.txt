project(ImGui)

include_directories(../GLFW/include)

set(PLATFORM_LIBS ../../platform/ImGui/imgui_impl_opengl3.cpp
        ../../platform/ImGui/imgui_impl_glfw.cpp)

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
#                                   ImGuiFileDialog.cpp
#                                   ImGuiFileDialog.h
#                                   ImGuiFileDialogConfig.h
#                                   implot.cpp
#                                   implot.h
#                                   implot_demo.cpp
#                                   implot_internal.h
#                                   implot_items.cpp
                                   ${PLATFORM_LIBS})