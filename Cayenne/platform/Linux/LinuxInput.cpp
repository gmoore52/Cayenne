#include <cayennepch.h>
#include "LinuxInput.h"
#include <Engine/Core/Application.h>
#include <GLFW/glfw3.h>

namespace Cayenne {
    Input* Input::c_Instance = new LinuxInput();

    bool LinuxInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetInstanceWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }

    float LinuxInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return x;
    }

    float LinuxInput::GetMouseYImpl()
    {
        auto[x, y] = GetMousePositionImpl();
        return y;
    }


} // Cayenne