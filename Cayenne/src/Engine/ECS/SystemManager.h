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
            m_Systems[SystemName]->UpdateComponents();
        }

        template<typename T>
        std::bitset<32> GetSignature()
        {
            auto && SystemName = typeid(T).name();
            return m_Signatures[SystemName];
        }

        void UpdateSystems(const Cayenne::Timestep& ts)
        {
            for(const auto &[Type, Sys] : m_Systems)
                Sys->Update(ts);
        }

    private:
        // Map from system type string pointer to a signature
        std::unordered_map<const char*, std::bitset<32>> m_Signatures;

        // Map from system type string pointer to a system pointer
        std::unordered_map<const char*, std::shared_ptr<System>> m_Systems;
    };

} // Cayenne

#endif //CAYENNE_SYSTEMMANAGER_H
