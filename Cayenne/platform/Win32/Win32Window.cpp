#include "Win32Window.h"

namespace Cayenne {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps &props)
    {
        return new Win32Window(props);
    }

    Win32Window::Win32Window(const WindowProps &props)
    {
        Init(props);
    }

    Win32Window::~Win32Window()
    {
        this->Shutdown();
    }

    void Win32Window::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        CY_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            CY_CORE_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback([](int error, const char* desc){
                CY_CORE_ERROR("GLFW error ({0}): {1}", error, desc);
            });
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Assign callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
                WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
                switch(action)
                {
                    case GLFW_PRESS:{
                        KeyPressedEvent event(key, 0);
                        data.EventCallback(event);
                        break;}
                    case GLFW_RELEASE:{
                        KeyReleasedEvent event(key);
                        data.EventCallback(event);
                        break;}
                    case GLFW_REPEAT:{
                        KeyPressedEvent event(key, 1);
                        data.EventCallback(event);
                        break;}
                }
            });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:{
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;}
                case GLFW_RELEASE:{
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;}
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xScroll, double yScroll)
        {
           WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

           MouseScrolledEvent event((float)xScroll, (float)yScroll);
           data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

    }

    void Win32Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void Win32Window::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void Win32Window::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool Win32Window::IsVSync() const
    {
        return m_Data.VSync;
    }
} // Cayenne