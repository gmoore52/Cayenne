#include <Engine/core.h>
#include <Engine/events/Event.h>
#ifndef CAYENNE_LAYER_H
#define CAYENNE_LAYER_H

namespace Cayenne
{
    class CY_API Layer {
    public:
        Layer(const std::string& name = "DefaultLayer");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() {return m_DebugName;}
    protected:
        std::string m_DebugName;
    };
}

#endif //CAYENNE_LAYER_H
