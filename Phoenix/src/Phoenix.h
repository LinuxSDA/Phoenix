//
//  Header.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

#include "px.pch"

/* For use by Phoenix applications */
#include "Phoenix/Application/Application.hpp"
#include "Phoenix/Application/Logger.hpp"
#include "Phoenix/Application/Layer.hpp"

#include "Phoenix/Application/Window.h"
#include "Phoenix/Application/Input.h"
#include "Phoenix/Application/ImGuiLayer.h"

#include "Phoenix/Application/KeyCodes.h"
#include "Phoenix/Application/MouseButtonCodes.h"

// ---Renderer------------------------
#include "Phoenix/Renderer/Interface/Renderer.hpp"
#include "Phoenix/Renderer/Interface/RenderCommand.hpp"

#include "Phoenix/Renderer/Interface/Buffer.hpp"
#include "Phoenix/Renderer/Interface/Shader.hpp"
#include "Phoenix/Renderer/Interface/VertexArray.hpp"

#include "Phoenix/Renderer/Interface/OrthographicCamera.hpp"
// -----------------------------------


// ---Entry point------------------------
#include "Phoenix/Application/EntryPoint.h"
