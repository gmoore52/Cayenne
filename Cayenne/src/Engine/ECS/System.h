#include <map>
#include <Engine/Core/Timestep.h>
#include "Component.h"
#ifndef CAYENNE_SYSTEM_H
#define CAYENNE_SYSTEM_H

namespace Cayenne
{
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void UpdateComponents() = 0;
        virtual void Update(const Timestep&) = 0;

    protected:
        std::map<int, std::shared_ptr<std::vector<std::shared_ptr<Component>>>> m_Components;

    };
}

#endif //CAYENNE_SYSTEM_H
