#pragma once

#include "Cyprium.h"

class Sandbox2D : public Cyprium::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Cyprium::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Cyprium::Event& e) override;
private:
	Cyprium::OrthographicCameraController m_CameraController;

	// Temp
	Cyprium::Ref<Cyprium::VertexArray> m_SquareVA;
	Cyprium::Ref<Cyprium::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};