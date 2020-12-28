//
//  OpenGLTexture.cpp
//  Phoenix
//
//  Created by SD on 23/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "OpenGLTexture.hpp"
#include "stb_image.h"

#include "Utils/ScopeExit.h"

#include <glad/glad.h>

namespace Phoenix
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
    {
        std::ifstream fstream(m_Path.c_str());
        PX_ENGINE_ASSERT(fstream.good(), "Filepath invalid!");

        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        AT_SCOPE_EXIT({ if(data) stbi_image_free(data); });
        
        PX_ENGINE_ASSERT(data, "Failed to load image!");

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;

        if (channels == 1)
        {
            dataFormat = GL_RED;
            internalFormat = GL_RED;
        }
        else if (channels == 3)
        {
            dataFormat = GL_RGB;
            internalFormat = GL_RGB8;
        }
        else if (channels == 4)
        {
            dataFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
                        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

}
