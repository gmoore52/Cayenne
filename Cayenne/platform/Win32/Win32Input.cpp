#include <cayennepch.h>
#include "Win32Input.h"
#include <Engine/Application.h>
#include <GLFW/glfw3.h>

namespace Cayenne {

    Input* Input::c_Instance = new Win32Input();

    bool Win32Input::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Win32Input::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Win32Input::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float Win32Input::GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return x;
    }

    float Win32Input::GetMouseYImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return y;
    }

} // Cayenne