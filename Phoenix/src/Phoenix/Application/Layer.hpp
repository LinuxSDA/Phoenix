//
//  Layers.hpp
//  Phoenix
//
//  Created by SD on 13/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Phoenix/Events/Event.h"

namespace Phoenix
{
    class LayerIDGenerator
    {
    public:
        static uint32_t Create();
        
        LayerIDGenerator() = delete;
        LayerIDGenerator(const LayerIDGenerator&) = delete;
        LayerIDGenerator& operator=(const LayerIDGenerator&) = delete;

    private:
        static uint32_t m_UniqueLayerID;
    };

    class Layer
    {
    public:
        using UniqueID = uint32_t;
        using UniquePtr = std::unique_ptr<Layer>;
        
        Layer(const std::string& name = "Layer");

        Layer(const Layer&) = delete;
        Layer& operator=(const Layer&) = delete;
        
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
        inline const UniqueID& GetLayerID() const { return m_UniqueLayerID;}

    protected:
        std::string m_DebugName;
        
    private:
        UniqueID m_UniqueLayerID;
    };

}
