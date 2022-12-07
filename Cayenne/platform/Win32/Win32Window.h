#include <Engine/Window.h>
#include <Engine/events/ApplicationEvent.h>
#include <Engine/events/KeyEvent.h>
#include <Engine/events/MouseEvent.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef CAYENNE_WIN32WINDOW_H
#define CAYENNE_WIN32WINDOW_H

namespace Cayenne {

    class Win32Window : public Window {
    public:
        Win32Window(const WindowProps& props);
        ~Win32Window() override;

        void OnUpdate() override;

        inline unsigned int GetWidth() const override {return m_Data.Width;}
        inline unsigned int GetHeight() const override {return m_Data.Height;}

        inline void SetEventCallback(const EventCallbackFn& callback) override {m_Data.EventCallback = callback;}
        void SetVSync(bool enabled);
        bool IsVSync() const;
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

} // Cayenne

#endif //CAYENNE_WIN32WINDOW_H
