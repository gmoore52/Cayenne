#include <Engine/Core/Input.h>
#ifndef CAYENNE_LINUXINPUT_H
#define CAYENNE_LINUXINPUT_H

namespace Cayenne {

    class LinuxInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

} // Cayenne

#endif //CAYENNE_LINUXINPUT_H
