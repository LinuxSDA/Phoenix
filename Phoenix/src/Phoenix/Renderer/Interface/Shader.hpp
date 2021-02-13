//
//  Shader.hpp
//  Phoenix
//
//  Created by SD on 29/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include <glm/matrix.hpp>

namespace Phoenix
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const std::string& GetName() const = 0;

        virtual void SetInt(const std::string& name, int value) const = 0;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) const = 0;

        virtual void SetFloat3(const std::string& name, const glm::vec3& value) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;

        virtual void SetMat3(const std::string& name, const glm::mat3& matrix) const = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const = 0;

        static Scope<Shader> Create(const std::string& filepath);
        static Scope<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary
    {
    public:
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);

        Ref<Shader> Get(const std::string& name) const;

        bool Exists(const std::string& name) const;

        static Scope<ShaderLibrary> Create();

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

}
