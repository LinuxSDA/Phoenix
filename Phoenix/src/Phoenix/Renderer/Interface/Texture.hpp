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
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Scope<Texture2D> Create(const std::string& path);
    };

}
