#include <cayennepch.h>
#include <set>
#include <bitset>

#include <Engine/Core/Timestep.h>
#include "Entity.h"
#include "System.h"
#include "Component.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

#ifndef CAYENNE_ECSMANAGER_H
#define CAYENNE_ECSMANAGER_H

namespace Cayenne {

    // Entity Component System manager class
    // Static wrapper class for the Entity, Component, and System managers
    class ECS {
    private:
        inline static std::unique_ptr<EntityManager>     m_EntityManager = std::make_unique<EntityManager>();
        inline static std::unique_ptr<ComponentManager>  m_ComponentManager = std::make_unique<ComponentManager>();
        inline static std::unique_ptr<SystemManager>     m_SystemManager = std::make_unique<SystemManager>();


    public:
        ECS();
        ECS(const ECS&) = delete;
        ECS& operator=(const ECS&) = delete;

        static std::shared_ptr<Entity> CreateEntity()
        {
            auto && entity = m_EntityManager->CreateEntity();
            CY_CORE_INFO("Created Entity: {0}", entity->EntityID);
            return entity;
        }

        static void DestroyEntity(Entity& entity)
        {
            m_EntityManager->DestroyEntity(entity);
            m_ComponentManager->DestroyEntity(entity);
        }

        template<typename TC>
        static void RegisterComponent()
        {
            m_ComponentManager->RegisterComponent<TC>();
        }

        template<typename TC>
        static void MountComponent(Entity& entity)
        {
            m_ComponentManager->AddComponent<TC>(entity);
            entity.EntityComponents.set(m_ComponentManager->GetComponentType<TC>(), true);

            m_EntityManager->SetSignature(entity, entity.EntityComponents);
        }

        template<typename TC>
        static void DetachComponent(Entity& entity)
        {
            m_ComponentManager->RemoveComponent<TC>(entity);
            entity.EntityComponents.set(m_ComponentManager->GetComponentType<TC>(), false);

            m_EntityManager->SetSignature(entity, entity.EntityComponents);
        }

        template<typename TC>
        static std::shared_ptr<TC> GetComponent(Entity& entity)
        {
            return m_ComponentManager->GetComponent<TC>(entity);
        }

        template<typename TC>
        static uint8_t GetComponentType()
        {
            return m_ComponentManager->GetComponentType<TC>();
        }

        static std::vector<std::shared_ptr<Component>>& GetComponentsFromID(int pos)
        {
            return m_ComponentManager->GetComponentVector(pos);
        }

        template<typename TS>
        static std::shared_ptr<TS> RegisterSystem()
        {
            return m_SystemManager->RegisterSystem<TS>();
        }

        template<typename TS>
        static void SetSystemSignature(std::bitset<32> signature)
        {
            m_SystemManager->SetSignature<TS>(signature);
        }

        template<typename TS>
        static std::bitset<32> GetSystemSignature()
        {
            return m_SystemManager->GetSignature<TS>();
        }

        static void OnUpdate(const Timestep& ts)
        {
            m_SystemManager->UpdateSystems(ts);
        }

    };

} // Cayenne

#endif //CAYENNE_ECSMANAGER_H
