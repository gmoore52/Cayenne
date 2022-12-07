#include <cayennepch.h>
#include <Engine/core.h>
#include <Engine/Window.h>
#include <Engine/LayerStack.h>
#include <Engine/events/Event.h>
#include <Engine/events/ApplicationEvent.h>
#include <glad/glad.h>

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
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* c_Instance;
    };


    Application* CreateApplication();
}

#endif //CAYENNE_APPLICATION_H