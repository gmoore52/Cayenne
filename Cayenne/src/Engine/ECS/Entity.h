#include <bitset>

#ifndef CAYENNE_ENTITY_H
#define CAYENNE_ENTITY_H
namespace Cayenne
{

//    using Entity = std::pair<uint32_t, std::bitset<32>> ;

    struct Entity
    {
        uint32_t EntityID;
        std::bitset<32> EntityComponents;

        Entity(uint32_t eID, const std::bitset<32>& ec) : EntityID(eID), EntityComponents(ec)
        {};

        // Because entities are stored in sets we need to overload the comparison operators for the Entity type so that it can be stored in sets
        bool operator <(const Entity& entityR) const
        {
            return (this->EntityID < entityR.EntityID);
        }
    };

}


#endif //CAYENNE_ENTITY_H
