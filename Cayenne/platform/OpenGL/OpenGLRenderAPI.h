#include <Engine/renderer/Renderer.h>
#ifndef CAYENNE_OPENGLRENDERAPI_H
#define CAYENNE_OPENGLRENDERAPI_H

namespace Cayenne {

    class OpenGLRenderAPI : public RendererAPI {
    public:
        virtual void Init() override;

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    };

} // Cayenne

#endif //CAYENNE_OPENGLRENDERAPI_H
