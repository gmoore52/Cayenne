#include <Engine/Input.h>
#ifndef CAYENNE_WIN32INPUT_H
#define CAYENNE_WIN32INPUT_H

namespace Cayenne {

    class Win32Input : public Input {
        protected:
            virtual bool IsKeyPressedImpl(int keycode) override;

            virtual bool IsMouseButtonPressedImpl(int button) override;
            virtual std::pair<float, float> GetMousePositionImpl() override;
            virtual float GetMouseXImpl() override;
            virtual float GetMouseYImpl() override;
        };

} // Cayenne

#endif //CAYENNE_WIN32INPUT_H
