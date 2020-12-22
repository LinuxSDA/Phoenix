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

        Layer::UniqueID PushLayer(Scope<Layer> layer);
        Layer::UniqueID PushOverlay(Scope<Layer> overlay);
        
        void PopLayer(Layer::UniqueID layerID);
        void PopOverlay(Layer::UniqueID layerID);

        std::optional<std::reference_wrapper<Layer>> Get(Layer::UniqueID layerID) const;
        
        std::deque<Scope<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::deque<Scope<Layer>>::iterator end() { return m_Layers.end(); }

        std::deque<Scope<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::deque<Scope<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }
        
        std::deque<Scope<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
        std::deque<Scope<Layer>>::const_iterator end() const { return m_Layers.end(); }

    private:
        std::deque<Scope<Layer>> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
}
