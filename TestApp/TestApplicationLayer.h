#include <Cayenne.h>
#include "Engine/ECS/ECS.h"

#ifndef CAYENNETESTPROJECT_TESTAPPLICATIONLAYER_H
#define CAYENNETESTPROJECT_TESTAPPLICATIONLAYER_H


class TestApplicationLayer : public Cayenne::Layer {
public:
    TestApplicationLayer();
    virtual ~TestApplicationLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Cayenne::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Cayenne::Event& e) override;
private:
    std::unique_ptr<Cayenne::ECS> c_ECSInstance;

    Cayenne::CameraController m_CameraController;

    // Temp
    std::shared_ptr<Cayenne::VertexArray> m_SquareVA;
    std::shared_ptr<Cayenne::Shader> m_FlatColorShader;

    std::shared_ptr<Cayenne::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    glm::vec2 m_SquarePos = {0.0f, 0.0f};

    std::shared_ptr<Cayenne::Entity> m_Entity;


};


#endif //CAYENNETESTPROJECT_TESTAPPLICATIONLAYER_H
