
#ifndef CAYENNE_COMPONENT_H
#define CAYENNE_COMPONENT_H

namespace Cayenne
{
    class Component
    {
    public:
        uint8_t ComponentID;
        virtual ~Component() = default;
    };
}

#endif //CAYENNE_COMPONENT_H
