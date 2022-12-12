#include <cayennepch.h>
#include "Shader.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLShader.h"

namespace Cayenne {

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // Cayenne