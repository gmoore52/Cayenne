#include <set>
#include "Entity.h"
#ifndef CAYENNE_SYSTEM_H
#define CAYENNE_SYSTEM_H

namespace Cayenne
{
    class ECS;
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void Update(const Timestep&, ECS*) = 0;

        std::set<Entity> m_Entities;
    };
}

#endif //CAYENNE_SYSTEM_H
