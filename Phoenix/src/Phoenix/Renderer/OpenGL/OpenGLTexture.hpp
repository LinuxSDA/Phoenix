//
//  OpenGLTexture.hpp
//  Phoenix
//
//  Created by SD on 23/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Phoenix/Renderer/Interface/Texture.hpp"

#include <glad/glad.h>

namespace Phoenix
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        OpenGLTexture2D(uint32_t width, uint32_t height, Format format);
        
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width;  }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void SetData(uint8_t* data, uint32_t size) override;

        virtual void Bind(uint32_t slot) const override;
        virtual void Unbind() const override;

        virtual bool Compare(const Texture& texture) const override;

    private:
        void SetGLFormat(int channel);
        void GenerateTexture();
        void SetTextureParams();
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        uint8_t m_Channels;
        GLenum m_InternalFormat = 0, m_DataFormat = 0;
    };

}
