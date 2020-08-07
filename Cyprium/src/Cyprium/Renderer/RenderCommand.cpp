#include "cppch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cyprium
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}