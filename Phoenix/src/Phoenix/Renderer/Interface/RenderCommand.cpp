//
//  RenderCommand.cpp
//  Phoenix
//
//  Created by SD on 30/11/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#include "px.pch"
#include "RenderCommand.hpp"

#include "Phoenix/Renderer/OpenGL/OpenGLRendererAPI.hpp"

namespace Phoenix
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}
