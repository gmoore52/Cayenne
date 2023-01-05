//
// Created by gavin on 12/11/2022.
//

#include "Texture.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLTexture.h"

namespace Cayenne {

    std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return std::make_shared<OpenGLTexture2D>(width, height);
        }

        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return std::make_shared<OpenGLTexture2D>(path);
        }

        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Cayenne