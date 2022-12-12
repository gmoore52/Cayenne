#include <cayennepch.h>
#include "OpenGLContext.h"

namespace Cayenne {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
            : m_WindowHandle(windowHandle)
    {
        CY_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CY_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
} // Cayenne