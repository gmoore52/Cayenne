#include <cayennepch.h>
#include <filesystem>
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image/stb_image.h"
#include "../lib/stb_image/tiff_image.h"

#include <glad/glad.h>

namespace Cayenne {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
            : m_Path(path) {
        int width, height, channels;
        std::filesystem::path file_path(path);

//        std::function<void>
        auto free_image = []() {};
        auto bind_data = [this](const int &w, const int &h, const int &c, unsigned char* data)
        {


        m_Width = w;
        m_Height = h;

        GLenum internalFormat = 0, dataFormat = 0;
        if (c == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (c == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        CY_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
        };

        if(file_path.extension() == ".jpg" || file_path.extension() == ".jpeg"
        || file_path.extension() == ".png") {
            stbi_set_flip_vertically_on_load(1);
            stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
            CY_CORE_ASSERT(data, "Failed to load image!");
            bind_data(width, height, channels, data);
            stbi_image_free(data);
        }
        else if(file_path.extension() == ".tif" || file_path.extension() == ".tiff")
        {
            TiffImage img;
            LoadTiffImage(path, img);
            unsigned char* data = img.pixels.data();
            if(img.pixels.empty())
                CY_CORE_ASSERT(data, "Img Failed to load !!");
            width = img.width; height = img.height;
            CY_CORE_ASSERT(data, "Failed to load image!");
            bind_data(width, height, 3, data);
        }
        else
            CY_CORE_ASSERT(data, "Image type not supported!");

    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }
} // Cayenne