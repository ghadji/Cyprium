#pragma once

#include "Cyprium/Core.h"
#include "Cyprium/Core/Timestep.h"
#include "Cyprium/Events/Event.h"

namespace Cyprium
{
	class CYPRIUM_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

