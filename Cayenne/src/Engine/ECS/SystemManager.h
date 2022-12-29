#include <cayennepch.h>
#include <bitset>

#include <Engine/Core/Timestep.h>
#include "System.h"
#include "Entity.h"

#ifndef CAYENNE_SYSTEMMANAGER_H
#define CAYENNE_SYSTEMMANAGER_H

namespace Cayenne {

    class ECS;
    class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            auto && SystemName = typeid(T).name();

            m_Systems[SystemName] = std::make_shared<T>();
            return std::dynamic_pointer_cast<T>(m_Systems[SystemName]);
        }

        template<typename T>
        void SetSignature(std::bitset<32> signature)
        {
            auto && SystemName = typeid(T).name();
            m_Signatures[SystemName] = signature;
        }

        void DestroyEntity(Entity& entity)
        {
            for(auto const &[Type, Sys] : m_Systems)
                Sys->m_Entities.erase(entity);
        }

        void EntitySignatureChanged(Entity& entity, std::bitset<32> entitySignature)
        {
            for(auto const &[Type, Sys] : m_Systems)
            {
                auto const& SysSignature = m_Signatures[Type];

                if((entitySignature & SysSignature) == SysSignature)
                    Sys->m_Entities.emplace(entity);

                else
                    Sys->m_Entities.emplace(entity);

            }
        }

        void UpdateSystems(const Cayenne::Timestep& ts, ECS* ecs)
        {
            for(const auto &[Type, Sys] : m_Systems)
                Sys->Update(ts, ecs);
        }

    private:
        // Map from system type string pointer to a signature
        std::unordered_map<const char*, std::bitset<32>> m_Signatures;

        // Map from system type string pointer to a system pointer
        std::unordered_map<const char*, std::shared_ptr<System>> m_Systems;
    };

} // Cayenne

#endif //CAYENNE_SYSTEMMANAGER_H
