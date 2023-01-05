#include <cayennepch.h>

#include "Component.h"
#include "Entity.h"

#ifndef CAYENNE_COMPONENTMANAGER_H
#define CAYENNE_COMPONENTMANAGER_H

namespace Cayenne {

    class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent()
        {
            auto && ComponentID = m_ComponentIDs[typeid(T).name()];
//            if(m_ComponentToVector[ComponentID].empty())
//                return;

            m_ComponentIDs[typeid(T).name()] = m_LastComponentID;

            m_ComponentToVector[ComponentID] = {};

            if(m_LastComponentID>=32)
                m_LastComponentID = 0;

            m_LastComponentID++;
        }

        template<typename T>
        uint8_t GetComponentType()
        {
            return m_ComponentIDs[typeid(T).name()];
        }

        template<typename T>
        void AddComponent(Entity& entity)
        {
            auto && CompVector = GetComponentVector<T>();
            auto && ComponentID = GetComponentType<T>();

            CompVector.emplace_back(std::make_shared<T>());
            m_IndexToEntities[ComponentID][CompVector.size()-1] = entity.EntityID;
            m_EntitiesToIndex[ComponentID][entity.EntityID] = CompVector.size()-1;
        }

        template<typename T>
        void RemoveComponent(Entity& entity)
        {
            auto && ComponentID = GetComponentType<T>();
            auto && ComponentPosition = m_EntitiesToIndex[ComponentID][entity.EntityID];

            // Remove data from relevant containers
            GetComponentVector<T>().erase(ComponentPosition);
            m_EntitiesToIndex[ComponentID].erase(entity.EntityID);
            m_IndexToEntities[ComponentID].erase(ComponentPosition);
        }

        template<typename T>
        std::shared_ptr<T> GetComponent(Entity& entity)
        {
            uint8_t && ComponentID = GetComponentType<T>();
            auto && CompVector = GetComponentVector<T>();

            return std::dynamic_pointer_cast<T>(CompVector[m_EntitiesToIndex[ComponentID][entity.EntityID]]);
        }

        void DestroyEntity(Entity& entity)
        {
            for(auto const &[Type, ID] : m_ComponentIDs)
            {
                if(m_EntitiesToIndex[ID].find(entity.EntityID) != m_EntitiesToIndex[ID].end())
                {
                    auto && Index = m_EntitiesToIndex[ID][entity.EntityID];
                    m_IndexToEntities[ID].erase(Index);
                    m_EntitiesToIndex[ID].erase(entity.EntityID);
                };
            }
        }

        std::vector<std::shared_ptr<Component>>& GetComponentVector(int pos)
        {
            return m_ComponentToVector[pos];
        }

    private:
        // Map from type string pointer to a component type
        std::unordered_map<const char*, uint8_t> m_ComponentIDs;

        // Map from type string pointer to a component array
        std::unordered_map<uint8_t, std::vector<std::shared_ptr<Component>>> m_ComponentToVector;

        // Map of maps that maps the index of the component data to the appropriate entity id
        // first map key is for the ID of the component
        std::unordered_map<uint8_t, std::unordered_map<size_t, uint32_t>> m_IndexToEntities;
        std::unordered_map<uint8_t, std::unordered_map<uint32_t, size_t>> m_EntitiesToIndex;

        // The component type to be assigned to the next registered component - starting at 1
        uint8_t m_LastComponentID = 1;

        // Convenience function to get the component vector
        template<typename T>
        std::vector<std::shared_ptr<Component>>& GetComponentVector()
        {
            return m_ComponentToVector[m_ComponentIDs[typeid(T).name()]];
        }

    };

} // Cayenne

#endif //CAYENNE_COMPONENTMANAGER_H
