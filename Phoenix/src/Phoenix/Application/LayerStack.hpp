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

        std::deque<Layer::UniquePtr>::iterator begin() { return m_Layers.begin(); }
        std::deque<Layer::UniquePtr>::iterator end() { return m_Layers.end(); }
        
    private:
        std::deque<Layer::UniquePtr> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
}
