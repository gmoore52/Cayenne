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
    class ECS {
    private:
        std::unique_ptr<EntityManager> m_EntityManager;
        std::unique_ptr<ComponentManager> m_ComponentManager;
        std::unique_ptr<SystemManager> m_SystemManager;

    public:
        ECS();
        ECS(const ECS&) = delete;
        ECS& operator=(const ECS&) = delete;

        std::shared_ptr<Entity> CreateEntity();

        void DestroyEntity(Entity entity);

        template<typename TComponent>
        void RegisterComponent()
        {
            m_ComponentManager->RegisterComponent<TComponent>();
        }

        template<typename TComponent>
        void MountComponent(Entity entity)
        {
            m_ComponentManager->AddComponent<TComponent>(entity);
            entity.EntityComponents.set(m_ComponentManager->GetComponentType<TComponent>(), true);

            m_EntityManager->SetSignature(entity, entity.EntityComponents);

            m_SystemManager->EntitySignatureChanged(entity, entity.EntityComponents);
        }

        template<typename TComponent>
        void DetachComponent(Entity entity)
        {
            m_ComponentManager->RemoveComponent<TComponent>(entity);
            entity.EntityComponents.set(m_ComponentManager->GetComponentType<TComponent>(), false);

            m_EntityManager->SetSignature(entity, entity.EntityComponents);

            m_SystemManager->EntitySignatureChanged(entity, entity.EntityComponents);
        }

        template<typename TComponent>
        std::shared_ptr<TComponent> GetComponent(Entity& entity)
        {
            return m_ComponentManager->GetComponent<TComponent>(entity);
        }

        template<typename TComponent>
        uint8_t GetComponentType()
        {
            return m_ComponentManager->template GetComponentType<TComponent>();
        }

        template<typename TSystem>
        std::shared_ptr<TSystem> RegisterSystem()
        {
            return m_SystemManager->RegisterSystem<TSystem>();
        }

        template<typename TSystem>
        void SetSystemSignature(std::bitset<32> signature)
        {
            m_SystemManager->SetSignature<TSystem>(signature);
        }

        void OnUpdate(const Timestep& ts);

    };

} // Cayenne

#endif //CAYENNE_ECSMANAGER_H
