#include <Engine/ECS/Component.h>
#include <glm/gtc/type_ptr.hpp>

#ifndef CAYENNE_SPRITE_H
#define CAYENNE_SPRITE_H

namespace Cayenne
{
    struct Sprite : public Component
    {
        glm::vec4 Color;
        glm::vec2 SquareSize, SquarePos;
        float Rotation;
    };
}
#endif //CAYENNE_SPRITE_H
