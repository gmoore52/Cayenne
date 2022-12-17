#include <cayennepch.h>
#include <Engine/Core/core.h>
#include <Engine/events/Event.h>

#ifndef CAYENNE_WINDOW_H
#define CAYENNE_WINDOW_H

namespace Cayenne {
    struct WindowProps {
        std::string Title;
        unsigned int Width,
                     Height;

        explicit WindowProps(const std::string &title = "Cayenne",
                             unsigned int width = 1280,
                             unsigned int height = 960) :
                             Title(title), Width(width), Height(height) {}
    };

    class CY_API Window
        {
                public:
                using EventCallbackFn = std::function<void(Event&)>;

                virtual ~Window() {};

                virtual void OnUpdate() = 0;

                virtual unsigned int GetWidth() const = 0;
                virtual unsigned int GetHeight() const = 0;

                virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
                virtual void SetVSync(bool enabled) = 0;
                virtual bool IsVSync() const = 0;

                virtual void* GetInstanceWindow() const = 0;

                static Window* Create(const WindowProps& props = WindowProps());
        };
}
#endif //CAYENNE_WINDOW_H
