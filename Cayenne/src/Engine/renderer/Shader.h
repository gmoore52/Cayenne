#ifndef CAYENNE_SHADER_H
#define CAYENNE_SHADER_H

namespace Cayenne {

    class Shader {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

} // Cayenne

#endif //CAYENNE_SHADER_H