#include <cayennepch.h>
#include "Renderer.h"
#include "../platform/OpenGL/OpenGLRenderAPI.h"
#include "../platform/OpenGL/OpenGLShader.h"

namespace Cayenne {

    RendererAPI* RenderCommand::c_RendererAPI = new OpenGLRenderAPI;
    RendererAPI::API RendererAPI::c_API = RendererAPI::API::OPENGL;

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // Cayenne