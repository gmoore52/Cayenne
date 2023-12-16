//
// Created by gavin on 12/15/23.
//

#include "LinuxWindow.h"

namespace Cayenne {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const Cayenne::WindowProps &props)
    {
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const Cayenne::WindowProps &props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        this->Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props)
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


        // Assign Callbacks
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
    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
} // Cayenne