//
//  Texture.hpp
//  Phoenix
//
//  Created by SD on 23/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

namespace Phoenix
{
    class Texture
    {
    public:
        
        enum Format
        {
            GrayScale = 1,
            RGB = 3,
            RGBA = 4
        };
        
        virtual ~Texture() = default;

        virtual uint32_t GetRendererID() const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetData(uint8_t* data, uint32_t size) = 0;
        
        virtual void Bind(uint32_t slot) const = 0;
        virtual void Unbind() const = 0;

        virtual bool Compare(const Texture& texture) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Scope<Texture2D> Create(uint32_t width, uint32_t height, Format format);
        static Scope<Texture2D> Create(const std::string& path);
    };

}
