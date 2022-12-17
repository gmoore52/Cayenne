#include <cayennepch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLVertexArray.h"

namespace Cayenne {
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return std::make_shared<OpenGLVertexArray>();
        }

        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Cayenne