#include "TestApplicationLayer.h"
#include "../Cayenne/lib/ImGui/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Engine/ECS/Systems/RenderSystem.h>
//#include <


//struct Position : public Cayenne::Component
//{
//    int x, y;
//};

//class Physics : public Cayenne::System
//{
//public:
//
//    Physics() : Cayenne::System() {};
//    ~Physics() override = default;
//
//    void Update(const Cayenne::Timestep& ts) override
//    {
//
//    }
//};

//struct Sprite : public Cayenne::Component
//{
//    glm::vec4 Color;
//    glm::vec2 SquareSize, SquarePos;
//    float Rotation;
//};

//extern Cayenne::ECS
//class RenderSystem : public Cayenne::System
//{
//public:
//    RenderSystem() : Cayenne::System() {};
//    ~RenderSystem() override = default;
//
//
//    void Update(const Cayenne::Timestep& ts) override
//    {
//        for(auto ent : m_Entities)
//        {
//            auto SpriteComp = Cayenne::ECS::GetComponent<Sprite>(ent);
//
//            Cayenne::Renderer2::DrawQuadRotate(SpriteComp->SquarePos, SpriteComp->SquareSize, SpriteComp->Rotation, SpriteComp->Color);
//
//        }
//    }
//};




TestApplicationLayer::TestApplicationLayer()
        : Layer("TestApplicationLayer"), m_CameraController(1280.0f / 960.0f, true)
{
}

void TestApplicationLayer::OnAttach()
{
    m_CheckerboardTexture = Cayenne::Texture2D::Create("assets/Checkerboard.png");
//    Cayenne::ECS::RegisterComponent<Position>();
//    auto PhysicsSystem = Cayenne::ECS::RegisterSystem<Physics>();
    auto RenderSys = Cayenne::ECS::RegisterSystem<Cayenne::RenderSystem>();

//    std::bitset<32> phySig;
//    phySig.set(Cayenne::ECS::GetComponentType<Position>());
//    Cayenne::ECS::SetSystemSignature<Physics>(phySig);

    std::bitset<32> renSig;
    renSig.set(Cayenne::ECS::GetComponentType<Cayenne::Sprite>());
    Cayenne::ECS::SetSystemSignature<Cayenne::RenderSystem>(renSig);

    m_Entity = Cayenne::ECS::CreateEntity();

    Cayenne::ECS::MountComponent<Cayenne::Sprite>(*m_Entity);

    auto entSprite = Cayenne::ECS::GetComponent<Cayenne::Sprite>(*m_Entity);

    entSprite->SquareSize = {1.4f, 1.4f};
//    entSprite->Color = { 0.8f, 0.2f, 0.3f, 1.0f };
    entSprite->SquarePos = {0.5f, 0.5f};





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

    auto entSprite = Cayenne::ECS::GetComponent<Cayenne::Sprite>(*m_Entity);
    entSprite->Color = m_SquareColor;
    entSprite->SquarePos = m_SquarePos;
    entSprite->Rotation = m_SquareRotate;
    Cayenne::Renderer2::BeginScene(m_CameraController.GetCamera());


    Cayenne::ECS::OnUpdate(ts);





//    auto entity = Cayenne::ECS::CreateEntity();

//    Cayenne::Renderer2::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
//    Cayenne::Renderer2::DrawQuad(m_SquarePos, { 0.5f, 0.5f }, m_SquareColor);
    Cayenne::Renderer2::DrawQuadRotate({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, 1.0f, m_CheckerboardTexture, 10.0f);
    Cayenne::Renderer2::EndScene();
}

void TestApplicationLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::SliderFloat2("Square Position", glm::value_ptr(m_SquarePos), -10, 10);
    ImGui::SliderFloat("Square Rotation", &m_SquareRotate, -1, 1);
    ImGui::End();
}

void TestApplicationLayer::OnEvent(Cayenne::Event& e)
{
    m_CameraController.OnEvent(e);
}