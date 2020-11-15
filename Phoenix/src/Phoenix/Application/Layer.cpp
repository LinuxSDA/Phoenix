//
//  Layers.cpp
//  Phoenix
//
//  Created by SD on 13/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "Layer.hpp"

namespace Phoenix
{
    uint32_t LayerIDGenerator::m_UniqueLayerID = 0;
    uint32_t LayerIDGenerator::Create() { return ++m_UniqueLayerID;}

    Layer::Layer(const std::string& debugName) : m_DebugName(debugName), m_UniqueLayerID(LayerIDGenerator::Create())
    {
    }

    Layer::~Layer()
    {

    }
}
