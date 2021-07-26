#pragma once

//** CORE **//
#include "Core/Application.h"
#include "Core/Window.h"

//** CAMERA **//
#include "Camera/Camera.h"

//** DEBUG **//
#include "Debug/Logger.h"

//** EVENTS **//
#include "Events/Event.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

//** GRAPHICS **//
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/Framebuffer.h"

//** INPUT **//
#include "Input/Input.h"
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

//** LAYER **//
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"

//** USER_INTERFACE **//
#include "UserInterface/UserInterface.h"

//** UTILITY **//
#include "Utility/ResourceManager.h"

//** TIME **//
#include "Time/Timer.h"

//** BASE **//
#include "Base.h"

//** THIRD_PARTY **//
#include <imgui.h>

//** SCENE **//
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

// entry point
#ifdef LIGHT_ENTRY_POINT
	#include "EntryPoint.h"
#endif
