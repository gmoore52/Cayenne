#include "Engine/Layer.h"
#include "Engine/events/KeyEvent.h"
#include "Engine/events/MouseEvent.h"
#include "Engine/events/ApplicationEvent.h"

#ifndef CAYENNE_IMGUILAYER_H
#define CAYENNE_IMGUILAYER_H

namespace Cayenne {

    class CY_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);
        float m_Time = 0.0f;
    };

} // Cayenne

#endif //CAYENNE_IMGUILAYER_H
