#include <Engine/ECS/Component.h>
#include <Engine/ECS/Entity.h>
#include <vector>

#ifndef CAYENNE_LOCALSCENE_H
#define CAYENNE_LOCALSCENE_H

namespace Cayenne
{
    struct LocalScene : public Component
    {
        std::vector<Entity> LiveEntities;
    };
}

#endif //CAYENNE_LOCALSCENE_H
