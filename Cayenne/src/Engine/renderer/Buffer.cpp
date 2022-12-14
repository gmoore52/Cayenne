#include "Buffer.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLBuffer.h"
namespace Cayenne {

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::NONE: CY_CORE_ASSERT(false, "Renderer API version currently not supported (NULL)"); return nullptr;
            case RendererAPI::API::OPENGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        CY_CORE_ASSERT(false, "Unknown Renderer API!!");
        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch(Renderer::GetAPI())
        {
            case RendererAPI::API::NONE: CY_CORE_ASSERT(false, "Renderer API version currently not supported (NULL)"); return nullptr;
            case RendererAPI::API::OPENGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
        }

        CY_CORE_ASSERT(false, "Unknown Renderer API!!");
        return nullptr;
    }
} // Cayenne