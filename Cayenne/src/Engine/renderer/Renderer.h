#include <glm/glm.hpp>
#include "VertexArray.h"
#include "Shader.h"
#include "OrthographicCamera.h"

#ifndef CAYENNE_RENDERER_H
#define CAYENNE_RENDERER_H

namespace Cayenne {

    // Renderer API
    class RendererAPI
    {
    public:

        enum class API {
            NONE = 0, OPENGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return c_API; }
    private:
        static API c_API;
    };

    // Render Command class

    class RenderCommand
    {
    public:
        inline static void SetClearColor(const glm::vec4& color)
        {
            c_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            c_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            c_RendererAPI->DrawIndexed(vertexArray);
        }
    private:
        static RendererAPI* c_RendererAPI;
    };
    // Renderer
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));;

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };

} // Cayenne

#endif //CAYENNE_RENDERER_H