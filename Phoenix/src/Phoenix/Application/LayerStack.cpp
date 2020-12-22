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
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
    }

    Layer::UniqueID LayerStack::PushLayer(Scope<Layer> layer)
    {
        auto id = layer->GetLayerID();
        layer->OnAttach();
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        ++m_LayerInsertIndex;
        
        return id;
    }

    Layer::UniqueID LayerStack::PushOverlay(Scope<Layer> overlay)
    {
        auto id = overlay->GetLayerID();
        overlay->OnAttach();
        m_Layers.emplace_back(std::move(overlay));

        return id;
    }

    void LayerStack::PopLayer(Layer::UniqueID layerID)
    {
        auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, [&layerID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == layerID;
        });
        
        if (it != m_Layers.end())
        {
            (*it)->OnDetach();
            m_Layers.erase(it);
            --m_LayerInsertIndex;
        }
    }

    void LayerStack::PopOverlay(Layer::UniqueID overlayID)
    {
        auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), [&overlayID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == overlayID;
        });

        if (it != m_Layers.end())
        {
            (*it)->OnDetach();
            m_Layers.erase(it);
        }
    }

    std::optional<std::reference_wrapper<Layer>> LayerStack::Get(Layer::UniqueID layerID) const
    {
        auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [&layerID] (const Scope<Layer>& layer) {
            return layer->GetLayerID() == layerID;
        });

        if (it != m_Layers.end())
            return std::optional<std::reference_wrapper<Layer>>{**it};
        
        return std::nullopt;
    }

}
