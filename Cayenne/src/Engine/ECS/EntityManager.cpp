#include "EntityManager.h"

namespace Cayenne {

    std::shared_ptr<Entity> EntityManager::CreateEntity()
    {
        auto entity = std::make_shared<Entity>(0,0);
        entity->EntityID = m_LastEntityID;
        m_LastEntityID++;
        return entity;
    }

    void EntityManager::DestroyEntity(Entity& entity)
    {
        m_EntitiesToSignatures[entity.EntityID].reset();
    }

    void EntityManager::SetSignature(Entity& entity, std::bitset<32> signature)
    {
        m_EntitiesToSignatures[entity.EntityID] = signature;
    }

    std::bitset<32> EntityManager::GetSignature(Entity& entity)
    {
        return m_EntitiesToSignatures[entity.EntityID];
    }
} // Cayenne