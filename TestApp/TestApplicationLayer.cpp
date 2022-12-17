#include "TestApplicationLayer.h"
#include "../Cayenne/lib/ImGui/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


TestApplicationLayer::TestApplicationLayer()
        : Layer("TestApplicationLayer"), m_CameraController(1280.0f / 960.0f, true)
{
}

void TestApplicationLayer::OnAttach()
{
    m_CheckerboardTexture = Cayenne::Texture2D::Create("assets/Checkerboard.png");


//        m_FlatColorShader = Cayenne::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
//
//        auto textureShader = m_ShaderLibrary.Load("assets/texture.glsl");

//        TextureShader.reset(Cayenne::Shader::Create("assets/texture.glsl"));

//        m_Texture = Cayenne::Texture2D::Create("assets/Iceberg.png");
//
//
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(textureShader)->Bind();
//        std::dynamic_pointer_cast<Cayenne::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
}

void TestApplicationLayer::OnDetach()
{
}

void TestApplicationLayer::OnUpdate(Cayenne::Timestep ts)
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Cayenne::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Cayenne::RenderCommand::Clear();

    Cayenne::Renderer2::BeginScene(m_CameraController.GetCamera());
    Cayenne::Renderer2::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Cayenne::Renderer2::DrawQuad(m_SquarePos, { 0.5f, 0.5f }, m_SquareColor);
    Cayenne::Renderer2::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
    Cayenne::Renderer2::EndScene();
}

void TestApplicationLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::SliderFloat2("Square Position", glm::value_ptr(m_SquarePos), -10, 10);
    ImGui::End();
}

void TestApplicationLayer::OnEvent(Cayenne::Event& e)
{
    m_CameraController.OnEvent(e);
}