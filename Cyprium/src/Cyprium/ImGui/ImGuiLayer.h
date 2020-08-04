#pragma once

#include "Cyprium/Layer.h"

#include "Cyprium/Events/KeyEvent.h"
#include "Cyprium/Events/MouseEvent.h"
#include "Cyprium/Events/ApplicationEvent.h"

namespace Cyprium
{
	class CYPRIUM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}