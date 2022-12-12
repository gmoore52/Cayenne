#include <Engine/renderer/Renderer.h>
#ifndef CAYENNE_OPENGLRENDERAPI_H
#define CAYENNE_OPENGLRENDERAPI_H

namespace Cayenne {

    class OpenGLRenderAPI : public RendererAPI {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

    };

} // Cayenne

#endif //CAYENNE_OPENGLRENDERAPI_H
