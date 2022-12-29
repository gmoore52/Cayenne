#include "TestApplicationLayer.h"
#include "../Cayenne/lib/ImGui/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Position : public Cayenne::Component
{
    int x, y;
};

class Physics : public Cayenne::System
{
public:

    Physics() : Cayenne::System() {};
    ~Physics() override = default;

    void Update(const Cayenne::Timestep& ts, Cayenne::ECS* ecs) override
    {

    }
};
struct Sprite : public Cayenne::Component
{
    glm::vec4 Color;
    glm::vec2 SquareSize, SquarePos;
};

extern Cayenne::ECS c_ECSInstance;
class RenderSystem : public Cayenne::System
{
public:
    RenderSystem() : Cayenne::System() {};
    ~RenderSystem() override = default;


    void Update(const Cayenne::Timestep& ts, Cayenne::ECS* ecs) override
    {
        for(auto ent : m_Entities)
        {
            auto SpriteComp = ecs->GetComponent<Sprite>(ent);

            Cayenne::Renderer2::DrawQuad(SpriteComp->SquarePos, SpriteComp->SquareSize, SpriteComp->Color);

        }
    }
};




TestApplicationLayer::TestApplicationLayer()
        : Layer("TestApplicationLayer"), m_CameraController(1280.0f / 960.0f, true)
{
    c_ECSInstance = std::make_unique<Cayenne::ECS>();
}

void TestApplicationLayer::OnAttach()
{
    m_CheckerboardTexture = Cayenne::Texture2D::Create("assets/Checkerboard.png");
    c_ECSInstance->RegisterComponent<Position>();
    auto PhysicsSystem = c_ECSInstance->RegisterSystem<Physics>();
    auto RenderSys = c_ECSInstance->RegisterSystem<RenderSystem>();

    std::bitset<32> phySig;
    phySig.set(c_ECSInstance->GetComponentType<Position>());
    c_ECSInstance->SetSystemSignature<Physics>(phySig);

    std::bitset<32> renSig;
    renSig.set(c_ECSInstance->GetComponentType<Sprite>());
    c_ECSInstance->SetSystemSignature<RenderSystem>(renSig);

    m_Entity = c_ECSInstance->CreateEntity();

    c_ECSInstance->MountComponent<Sprite>(*m_Entity);

    auto entSprite = c_ECSInstance->GetComponent<Sprite>(*m_Entity);

    entSprite->SquareSize = {1.4f, 1.4f};
    entSprite->Color = { 0.8f, 0.2f, 0.3f, 1.0f };
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



    Cayenne::Renderer2::BeginScene(m_CameraController.GetCamera());


    c_ECSInstance->OnUpdate(ts);





//    auto entity = c_ECSInstance->CreateEntity();

//    Cayenne::Renderer2::DrawQuad({ -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
//    Cayenne::Renderer2::DrawQuad(m_SquarePos, { 0.5f, 0.5f }, m_SquareColor);
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