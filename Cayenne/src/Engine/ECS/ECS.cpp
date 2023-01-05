#include "ECS.h"

namespace Cayenne {

    ECS::ECS()
    {
        m_EntityManager = std::make_unique<EntityManager>();
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_SystemManager = std::make_unique<SystemManager>();
    }

    std::shared_ptr<Entity> ECS::CreateEntity()
    {
        auto && entity = m_EntityManager->CreateEntity();
        CY_CORE_INFO("Created Entity: {0}", entity->EntityID);
        return entity;
    }

    void ECS::DestroyEntity(Entity entity)
    {
        m_EntityManager->DestroyEntity(entity);
        m_ComponentManager->DestroyEntity(entity);
        m_SystemManager->DestroyEntity(entity);
    }

    void ECS::OnUpdate(const Timestep& ts)
    {
        m_SystemManager->UpdateSystems(ts);
    }
} // Cayenne