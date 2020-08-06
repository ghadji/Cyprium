#include <cppch.h>
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Cyprium
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:			CP_CORE_ASSERT(false, "RendererAPI None is not supported!"); return nullptr;
			case RendererAPI::OpenGL:		return new OpenGLVertexBuffer(vertices, size);
		}
		CP_CORE_ASSERT(false, "Unknown RendererAPI specified!");
		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:			CP_CORE_ASSERT(false, "RendererAPI None is not supported!"); return nullptr;
			case RendererAPI::OpenGL:		return new OpenGLIndexBuffer(indices, size);
		}
		CP_CORE_ASSERT(false, "Unknown RendererAPI specified!");
		return nullptr;
	}
}