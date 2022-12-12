#include <cayennepch.h>
#ifndef CAYENNE_TEXTURE_H
#define CAYENNE_TEXTURE_H

namespace Cayenne {

    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static std::shared_ptr<Texture2D> Create(const std::string& path);
    };

} // Cayenne

#endif //CAYENNE_TEXTURE_H
