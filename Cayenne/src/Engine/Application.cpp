#include "Application.h"
namespace Cayenne
{
    Application* Application::c_Instance = nullptr;

    Application::Application()
    {
        CY_CORE_ASSERT(!s_Instance, "Application already exists");
        c_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::EventHandler));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::EventHandler(Event &event) {
        if(event.GetEventType() == EventType::WindowClose)
            m_Window = nullptr;

        EventDispatcher dispatcher(event);
//        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }

//        CY_CORE_INFO("{0}", event);
    }

    void Application::Run()
    {
        while (m_Running)
        {
//            m_LayerStack.begin()->data->OnUpdate();
            for (Layer *layer : m_LayerStack)
                layer->OnUpdate();
            m_Window->OnUpdate();
        }
    }

}