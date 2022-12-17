#include <cayennepch.h>
#include "Shader.h"
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLShader.h"

namespace Cayenne {
    std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return std::make_shared<OpenGLShader>(filepath);
        }

        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::NONE:    CY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OPENGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
        CY_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    void ShaderLib::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        CY_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLib::Add(const std::shared_ptr<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    std::shared_ptr<Cayenne::Shader> ShaderLib::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    std::shared_ptr<Cayenne::Shader> ShaderLib::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    std::shared_ptr<Cayenne::Shader> ShaderLib::Get(const std::string& name)
    {
        CY_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLib::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }

} // Cayenne