#ifndef CAYENNE_INPUT_H
#define CAYENNE_INPUT_H

#include <Engine/Core/core.h>

namespace Cayenne {
    class CY_API Input
            {
            public:
                inline static bool IsKeyPressed(int keycode) { return c_Instance->IsKeyPressedImpl(keycode); }

                inline static bool IsMouseButtonPressed(int button) { return c_Instance->IsMouseButtonPressedImpl(button); }
                inline static std::pair<float, float> GetMousePosition() { return c_Instance->GetMousePositionImpl(); }
                inline static float GetMouseX() { return c_Instance->GetMouseXImpl(); }
                inline static float GetMouseY() { return c_Instance->GetMouseYImpl(); }
            protected:
                virtual bool IsKeyPressedImpl(int keycode) = 0;

                virtual bool IsMouseButtonPressedImpl(int button) = 0;
                virtual std::pair<float, float> GetMousePositionImpl() = 0;
                virtual float GetMouseXImpl() = 0;
                virtual float GetMouseYImpl() = 0;
            private:
                static Input* c_Instance;
            };
}

#endif //CAYENNE_INPUT_H