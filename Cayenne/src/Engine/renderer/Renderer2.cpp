#include <cayennepch.h>
#include "Renderer2.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cayenne {
    struct RendererStorage2
    {
        std::shared_ptr<VertexArray> QuadArray;
        std::shared_ptr<Shader> ColorShader;
        std::shared_ptr<Shader> TextureShader;
    };

    static RendererStorage2* c_Data;

    void Renderer2::Init()
    {
        c_Data = new RendererStorage2();
        c_Data->QuadArray = VertexArray::Create();

        float squareVertices[5*4] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        c_Data->QuadArray->AddVertexBuffer(squareVB);

        uint32_t squareIndecies[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB = IndexBuffer::Create(squareIndecies, sizeof(squareIndecies)/sizeof(uint32_t));

        c_Data->QuadArray->SetIndexBuffer(squareIB);
        c_Data->ColorShader = Shader::Create("assets/flatcolor.glsl");
        c_Data->TextureShader = Shader::Create("assets/texture.glsl");
        c_Data->TextureShader->Bind();
        c_Data->TextureShader->SetInt("u_Texture", 0);

//        if(c_Data->ColorShader == nullptr)
//            CY_CORE_ASSERT(c_Data, "Shader not loaded!");
    }

    void Renderer2::Shutdown()
    {
        delete c_Data;
    }

    void Renderer2::BeginScene(const OrthographicCamera& camera)
    {
        c_Data->ColorShader->Bind();
        c_Data->ColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        c_Data->TextureShader->Bind();
        c_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2::EndScene()
    {

    }

    void Renderer2::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({pos.x, pos.y, 0.0f}, size, color);
    }

    void Renderer2::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
    {
        c_Data->ColorShader->Bind();
        c_Data->ColorShader->SetFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        c_Data->ColorShader->SetMat4("u_Transform", transform);

        c_Data->QuadArray->Bind();
        RenderCommand::DrawIndexed(c_Data->QuadArray);
    }

    void Renderer2::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
    {
        DrawQuad({pos.x, pos.y, 0.0f}, size, texture);
    }


    void Renderer2::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture)
    {
        c_Data->TextureShader->Bind();

        glm::mat4 transform =
                glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        c_Data->TextureShader->SetMat4("u_Transform", transform);

        texture->Bind();

        c_Data->QuadArray->Bind();
        RenderCommand::DrawIndexed(c_Data->QuadArray);
    }

} // Cayenne
