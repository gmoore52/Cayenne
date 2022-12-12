#include <cayennepch.h>
#include <Engine/core.h>
#include <Engine/Window.h>
#include <Engine/LayerStack.h>
#include <Engine/events/Event.h>
#include <Engine/events/ApplicationEvent.h>
#include <Engine/DataLoader.h>
#include <ImGui/ImGuiLayer.h>

#ifndef CAYENNE_APPLICATION_H
#define CAYENNE_APPLICATION_H

namespace Cayenne {
    class CY_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void EventHandler(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }

        inline static Application& Get() { return *c_Instance; }
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool OnWindowClose(WindowCloseEvent& e);

        LayerStack m_LayerStack;

        float m_LastFrameTime = 0.0f;

        static Application* c_Instance;
    };


    Application* CreateApplication();
}

#endif //CAYENNE_APPLICATION_H