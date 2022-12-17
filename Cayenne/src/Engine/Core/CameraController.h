#include <Engine/renderer/OrthographicCamera.h>
#include "Timestep.h"
#include <Engine/events/ApplicationEvent.h>
#include <Engine/events/MouseEvent.h>

#ifndef CAYENNE_CAMERACONTROLLER_H
#define CAYENNE_CAMERACONTROLLER_H

namespace Cayenne {

    class CameraController {
    public:
        CameraController(float aspectRatio, bool rotate = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() {return m_Camera;}

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPos = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation,
              m_CameraTranslationSpeed = 5.0f,
              m_CameraRotationSpeed = 100.0f;

        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

    };

} // Cayenne

#endif //CAYENNE_CAMERACONTROLLER_H
