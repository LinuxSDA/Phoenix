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

        uint32_t PushLayer(Scope<Layer> layer);
        uint32_t PushOverlay(Scope<Layer> overlay);
        
        void PopLayer(uint32_t layerID);
        void PopOverlay(uint32_t layerID);

        Layer& Get(uint32_t layerID) const;
        
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
