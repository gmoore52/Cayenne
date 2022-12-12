#include <Engine/renderer/Context.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#ifndef CAYENNE_OPENGLCONTEXT_H
#define CAYENNE_OPENGLCONTEXT_H

namespace Cayenne {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };

} // Cayenne

#endif //CAYENNE_OPENGLCONTEXT_H
