#include <cayennepch.h>
#include <bitset>
#include <set>

#include "Entity.h"

#ifndef CAYENNE_ENTITYMANAGER_H
#define CAYENNE_ENTITYMANAGER_H

namespace Cayenne {

    class EntityManager {
    public:
        EntityManager() = default;

        std::shared_ptr<Entity> CreateEntity();

        void DestroyEntity(Entity& entity);

        void SetSignature(Entity& entity, std::bitset<32> signature);

        std::bitset<32> GetSignature(Entity& entity);

    private:
        // Set of used entity IDs
        std::set<uint32_t> m_UsedIDs;

        // Array of signatures where the index corresponds to the entity ID
        std::unordered_map<uint32_t, std::bitset<32>> m_EntitiesToSignatures;

        uint32_t m_LastEntityID = 0;
    };

} // Cayenne

#endif //CAYENNE_ENTITYMANAGER_H
