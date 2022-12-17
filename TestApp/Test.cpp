#include <Cayenne.h>
#include <Engine/Core/EntryPoint.h>
#include "TestApplicationLayer.h"

//class ExampleLayer : public Cayenne::Layer
//{
//public:
//    ExampleLayer()
//            : Layer("Example"), m_CameraController(1280.0f / 720.0f, false)
//    {
//        m_VertexArray.reset(Cayenne::VertexArray::Create());
//
//        float vertices[3 * 7] = {
//                -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
//                0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
//                0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
//        };
//
//        std::shared_ptr<Cayenne::VertexBuffer> vertexBuffer;
//        vertexBuffer.reset(Cayenne::VertexBuffer::Create(vertices, sizeof(vertices)));
//        Cayenne::BufferLayout layout = {
//                { Cayenne::ShaderDataType::Float3, "a_Position" },
//                { Cayenne::ShaderDataType::Float4, "a_Color" }
//        };
//        vertexBuffer->SetLayout(layout);
//        m_VertexArray->AddVertexBuffer(vertexBuffer);
//
//        uint32_t indices[3] = { 0, 1, 2 };
//        std::shared_ptr<Cayenne::IndexBuffer> indexBuffer;
//        indexBuffer.reset(Cayenne::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
//        m_VertexArray->SetIndexBuffer(indexBuffer);
//
//        m_SquareVA.reset(Cayenne::VertexArray::Create());
//
//        float squareVertices[5 * 4] = {
//                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//                0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
//                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
//        };
//
//        std::shared_ptr<Cayenne::VertexBuffer> squareVB;
//        squareVB.reset(Cayenne::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
//        squareVB->SetLayout({
//                                    { Cayenne::ShaderDataType::Float3, "a_Position" },
//                                    { Cayenne::ShaderDataType::Float2, "a_TexCoord" }
//                            });
//        m_SquareVA->AddVertexBuffer(squareVB);
//
//        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
//        std::shared_ptr<Cayenne::IndexBuffer> squareIB;
//        squareIB.reset(Cayenne::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
//        m_SquareVA->SetIndexBuffer(squareIB);
//
//        std::string vertexSrc = R"(
//			#version 330 core
//
//			layout(location = 0) in vec3 a_Position;
//			layout(location = 1) in vec4 a_Color;
//			uniform mat4 u_ViewProjection;
//            uniform mat4 u_Transform;
//			out vec3 v_Position;
//			out vec4 v_Color;
//			void main()
//			{
//				v_Position = a_Position;
//				v_Color = a_Color;
//				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
//			}
//		)";
//
//        std::string fragmentSrc = R"(
//			#version 330 core
//
//			layout(location = 0) out vec4 color;
//			in vec3 v_Position;
//			in vec4 v_Color;
//			void main()
//			{
//				color = vec4(v_Position * 0.5 + 0.5, 1.0);
//				color = v_Color;
//			}
//		)";
//
//        m_Shader = Cayenne::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
//
//        std::string flatColorShaderVertexSrc = R"(
//			#version 330 core
//
//			layout(location = 0) in vec3 a_Position;
//			uniform mat4 u_ViewProjection;
//            uniform mat4 u_Transform;
//			out vec3 v_Position;
//			void main()
//			{
//				v_Position = a_Position;
//				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
//			}
//		)";
//
//        std::string flatColorShaderFragmentSrc = R"(
//			#version 330 core
//
//			layout(location = 0) out vec4 color;
//			in vec3 v_Position;
//
//            uniform vec3 u_Color;
//
//			void main()
//			{
//				color = vec4(u_Color, 1.0);
//			}
//		)";
//
//        m_FlatColorShader = Cayenne::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
//
//        auto textureShader = m_ShaderLibrary.Load("assets/texture.glsl");
//
////        TextureShader.reset(Cayenne::Shader::Create("assets/texture.glsl"));
//
//        m_Texture = Cayenne::Texture2D::Create("assets/Iceberg.png");
//
//
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(textureShader)->Bind();
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
//    }
//
//    void OnUpdate(Cayenne::Timestep ts) override
//    {
//        m_CameraController.OnUpdate(ts);
//
//
//
//        Cayenne::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
//        Cayenne::RenderCommand::Clear();
//
//        Cayenne::Renderer::BeginScene(m_CameraController.GetCamera());
//
//        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
//
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(m_FlatColorShader)->Bind();
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
//
//        for (int y = 0; y < 20; y++)
//        {
//            for (int x = 0; x < 20; x++)
//            {
//                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
//                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
//                Cayenne::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
//            }
//        }
//
//        auto textureShader = m_ShaderLibrary.Get("texture");
//
//        Cayenne::Renderer::Submit(m_Shader, m_VertexArray);
//
//        Cayenne::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
//        m_Texture->Bind();
////        Cayenne::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
//
//
//        Cayenne::Renderer::EndScene();
//    }
//
//    virtual void OnImGuiRender() override
//    {
//        ImGui::Begin("Settings");
//        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
//        ImGui::End();
//    }
//
//    void OnEvent(Cayenne::Event& event) override
//    {
//        m_CameraController.OnEvent(event);
//    };
//
//private:
//    Cayenne::ShaderLib m_ShaderLibrary;
//
//    std::shared_ptr<Cayenne::Shader> m_Shader;
//    std::shared_ptr<Cayenne::VertexArray> m_VertexArray;
//
//    std::shared_ptr<Cayenne::Shader> m_FlatColorShader;
//    std::shared_ptr<Cayenne::VertexArray> m_SquareVA;
//    std::shared_ptr<Cayenne::Texture2D> m_Texture;
//
//    Cayenne::CameraController m_CameraController;
//
//    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
//};

class TestApp : public Cayenne::Application
{
public:
    TestApp()
    {
        PushLayer(new TestApplicationLayer());
//        PushOverlay(new Cayenne::ImGuiLayer());
    }

    ~TestApp()
    {

    }
};

Cayenne::Application* Cayenne::CreateApplication()
{
    return new TestApp();
}