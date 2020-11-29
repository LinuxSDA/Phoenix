//
//  LayerStack.hpp
//  Phoenix
//
//  Created by SD on 13/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "px.pch"
#include "Core.h"
#include "Layer.hpp"

namespace Phoenix
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        Layer::UniqueID PushLayer(Layer::UniquePtr layer);
        Layer::UniqueID PushOverlay(Layer::UniquePtr overlay);
        
        void PopLayer(Layer::UniqueID layerID);
        void PopOverlay(Layer::UniqueID layerID);

        std::optional<std::reference_wrapper<Layer>> Get(Layer::UniqueID layerID) const;
        
        std::deque<Layer::UniquePtr>::iterator begin() { return m_Layers.begin(); }
        std::deque<Layer::UniquePtr>::iterator end() { return m_Layers.end(); }

        std::deque<Layer::UniquePtr>::const_iterator begin() const { return m_Layers.begin(); }
        std::deque<Layer::UniquePtr>::const_iterator end() const { return m_Layers.end(); }

    private:
        std::deque<Layer::UniquePtr> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
}
