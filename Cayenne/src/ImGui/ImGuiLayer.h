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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    };

} // Cayenne

#endif //CAYENNE_IMGUILAYER_H
