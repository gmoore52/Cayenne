#include "OrthographicCamera.h"
#include "Texture.h"
#ifndef CAYENNE_RENDERER2_H
#define CAYENNE_RENDERER2_H

namespace Cayenne {

    class Renderer2 {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // draw square
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 &tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f, const glm::vec4 &tint = glm::vec4(1.0f));


        static void DrawQuadRotate(const glm::vec2& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuadRotate(const glm::vec3& pos, const glm::vec2& size, float rotation, const glm::vec4& color);
        static void DrawQuadRotate(const glm::vec2& pos, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling = 1.0f, const glm::vec4 &tint = glm::vec4(1.0f));
        static void DrawQuadRotate(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const std::shared_ptr<Texture2D> &texture, float tiling = 1.0f, const glm::vec4 &tint = glm::vec4(1.0f));
//        static void DrawTriangle(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
//        static void DrawTriangle(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
//        static void DrawTriangle(const glm::vec2& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
//        static void DrawTriangle(const glm::vec3& pos, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture);
    };

} // Cayenne

#endif //CAYENNE_RENDERER2_H
