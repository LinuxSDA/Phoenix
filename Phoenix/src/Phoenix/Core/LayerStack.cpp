//
//  LayerStack.cpp
//  Phoenix
//
//  Created by SD on 13/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "LayerStack.hpp"

namespace Phoenix
{
    /* TODO: On Attach and on detach should not be called in here. but rather from Application. FIX it. */
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        PX_PROFILE_FUNCTION();

        for(auto& layer: m_Layers)
            layer->OnDetach();
    }

    uint32_t LayerStack::PushLayer(Scope<Layer> layer)
    {
        PX_PROFILE_FUNCTION();

        auto id = layer->GetLayerID();
        layer->OnAttach();
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        ++m_LayerInsertIndex;
        
        return id;
    }

    uint32_t LayerStack::PushOverlay(Scope<Layer> overlay)
    {
        PX_PROFILE_FUNCTION();

        auto id = overlay->GetLayerID();
        overlay->OnAttach();
        m_Layers.emplace_back(std::move(overlay));

        return id;
    }

    void LayerStack::PopLayer(uint32_t layerID)
    {
        PX_PROFILE_FUNCTION();

        auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, [&layerID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == layerID;
        });
        
        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
            (*it)->OnDetach();
            m_Layers.erase(it);
            --m_LayerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(uint32_t overlayID)
    {
        PX_PROFILE_FUNCTION();

        auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), [&overlayID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == overlayID;
        });

        if (it != m_Layers.end())
        {
            (*it)->OnDetach();
            m_Layers.erase(it);
        }
    }

    Layer& LayerStack::Get(uint32_t layerID) const
    {
        PX_PROFILE_FUNCTION();

        auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&layerID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == layerID;
        });

        if (it != m_Layers.end())
            return (**it);

        throw std::runtime_error("Layer not found!");
    }
}
