#include <cayennepch.h>
#include "VertexArray.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLVertexArray.h"

namespace Cayenne {
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return new OpenGLVertexArray();
        }

        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Cayenne