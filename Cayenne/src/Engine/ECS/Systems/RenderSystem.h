#include <Engine/ECS/ECS.h>
#include <Engine/Core/Timestep.h>

#include <Engine/ECS/Components/Sprite.h>

#ifndef CAYENNE_RENDERSYSTEM_H
#define CAYENNE_RENDERSYSTEM_H

namespace Cayenne
{
    // TODO: Find what in this system is causing a shared pointer to be deleted twice and fix it (only happens on destruction)
    class RenderSystem : public System
    {
    public:
        void UpdateComponents() override
        {
            auto && SystemSignature = ECS::GetSystemSignature<RenderSystem>();
            for(int i = 0; i < SystemSignature.size(); i++)
            {
                auto &&ComponentPointer = &ECS::GetComponentsFromID(i);

                if(SystemSignature.test(i))
                    m_Components.emplace(i, ComponentPointer);
            }
        }

        RenderSystem() : System()
        {
            this->UpdateComponents();
        };
        ~RenderSystem() override = default;


        void Update(const Timestep& ts) override
        {
            CY_CORE_INFO("m_Components: {0}", m_Components.size());
            for(auto &[CompID, CompVecPtr] : m_Components)
            {
                if(CompID == ECS::GetComponentType<Sprite>())
                {

                    for(auto &sprite : *CompVecPtr)
                    {
                        auto && newSprite = std::dynamic_pointer_cast<Sprite>(sprite);
                        newSprite->SquareSize = {1.0f, 1.0f};
                        Cayenne::Renderer2::DrawQuadRotate(newSprite->SquarePos, newSprite->SquareSize, newSprite->Rotation, newSprite->Color);
                    }
                }

//                if (CompID == ECS::)
//                {
//
//                }
            }
        }


    };
}


#endif //CAYENNE_RENDERSYSTEM_H
