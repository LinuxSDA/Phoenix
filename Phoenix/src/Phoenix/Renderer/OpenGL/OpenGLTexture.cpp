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

#include "Phoenix/Utils/ScopeExit.h"

namespace Phoenix
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
    {
        PX_PROFILE_FUNCTION();

        std::ifstream fstream(m_Path.c_str());
        PX_ENGINE_ASSERT(fstream.good(), "Filepath invalid!");

        int width, height, channels;

        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        AT_SCOPE_EXIT({ if(data) stbi_image_free(data); });
        
        PX_ENGINE_ASSERT(data, "Failed to load image!");

        m_Width = width;
        m_Height = height;
        m_Channels = channels;
        
        SetGLFormat(channels);

        GenerateTexture();
        SetTextureParams();
        SetData(data, m_Width * m_Height * m_Channels);
        Unbind();
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, Format format) : m_Width(width), m_Height(height), m_Channels(format)
    {
        PX_PROFILE_FUNCTION();

        SetGLFormat(m_Channels);

        GenerateTexture();
        SetTextureParams();
        SetData(nullptr, m_Width * m_Height * m_Channels);
        Unbind();
    }

    void OpenGLTexture2D::SetGLFormat(int channels)
    {
        PX_PROFILE_FUNCTION();

        if (m_Channels == 1)
        {
            m_DataFormat = GL_RED;
            m_InternalFormat = GL_RED;
        }
        else if (m_Channels == 3)
        {
            m_DataFormat = GL_RGB;
            m_InternalFormat = GL_RGB8;
        }
        else if (m_Channels == 4)
        {
            m_DataFormat = GL_RGBA;
            m_InternalFormat = GL_RGBA8;
        }
        else
        {
            PX_ENGINE_ASSERT(false, "Bad channel request!");
        }
    }

    void OpenGLTexture2D::GenerateTexture()
    {
        PX_PROFILE_FUNCTION();

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void OpenGLTexture2D::SetTextureParams()
    {
        PX_PROFILE_FUNCTION();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void OpenGLTexture2D::SetData(uint8_t* data, uint32_t size)
    {
        PX_PROFILE_FUNCTION();

        PX_ENGINE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire texture!");
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }


    OpenGLTexture2D::~OpenGLTexture2D()
    {
        PX_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        PX_PROFILE_FUNCTION();

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void OpenGLTexture2D::Unbind() const
    {
        PX_PROFILE_FUNCTION();

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    bool OpenGLTexture2D::Compare(const Texture& texture) const
    {
        // TODO: Try catch #define
        try
        {
            return (m_RendererID == dynamic_cast<const OpenGLTexture2D&>(texture).m_RendererID);
        }
        catch (...) {}

        return false;
    }
}
