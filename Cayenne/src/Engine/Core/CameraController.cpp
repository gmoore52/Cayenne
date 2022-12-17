#include <cayennepch.h>
#include "CameraController.h"

#include <Engine/Core/Input.h>
#include <Engine/Core/InputCodes.h>

namespace Cayenne {

    CameraController::CameraController(float aspectRatio, bool rotation)
            : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {
    }

    void CameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(CY_KEY_A))
            m_CameraPos.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(CY_KEY_D))
            m_CameraPos.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(CY_KEY_W))
            m_CameraPos.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(CY_KEY_S))
            m_CameraPos.y -= m_CameraTranslationSpeed * ts;

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(CY_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            if (Input::IsKeyPressed(CY_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPos);

        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void CameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::OnWindowResized));
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool CameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
} // Cayenne