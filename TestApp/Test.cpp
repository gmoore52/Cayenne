#include <Cayenne.h>

class ExampleLayer : public Cayenne::Layer
{
public:
    ExampleLayer()
            : Layer("Example")
    {
    }

    void OnUpdate() override
    {
//        CY_INFO("ExampleLayer::Update");
    }

    void OnEvent(Cayenne::Event& event) override {
        CY_TRACE("Example: {0}", event);

    };
};

class TestApp : public Cayenne::Application
{
public:
    TestApp()
    {
//        PushLayer(new ExampleLayer());
        PushOverlay(new Cayenne::ImGuiLayer());
    }

    ~TestApp()
    {

    }
};

Cayenne::Application* Cayenne::CreateApplication()
{
    return new TestApp();
}