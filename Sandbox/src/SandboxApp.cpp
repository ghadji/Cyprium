#include <Cyprium.h>

#include "imgui/imgui.h"

class ExampleLayer : public Cyprium::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Cyprium::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Cyprium::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cyprium::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cyprium::BufferLayout layout = {
			{ Cyprium::ShaderDataType::Float3, "a_Position" },
			{ Cyprium::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Cyprium::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cyprium::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Cyprium::VertexArray::Create());

		float squareVertices[3 * 4] = {
			 -0.75f, -0.75f, 0.0f,
			  0.75f, -0.75f, 0.0f,
			  0.75f,  0.75f, 0.0f,
			 -0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Cyprium::VertexBuffer> squareVB;
		squareVB.reset(Cyprium::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Cyprium::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Cyprium::IndexBuffer> squareIB;
		squareIB.reset(Cyprium::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Cyprium::Shader(vertexSrc, fragmentSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Cyprium::Shader(blueVertexSrc, blueFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Cyprium::Input::IsKeyPressed(CP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Cyprium::Input::IsKeyPressed(CP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Cyprium::Input::IsKeyPressed(CP_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;


		Cyprium::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cyprium::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cyprium::Renderer::BeginScene(m_Camera);

		Cyprium::Renderer::Submit(m_SquareVA, m_BlueShader);
		Cyprium::Renderer::Submit(m_VertexArray, m_Shader);

		Cyprium::Renderer::EndScene();
	}
	
	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Cyprium::Event& event) override
	{

	}
private:
	std::shared_ptr<Cyprium::Shader> m_Shader;
	std::shared_ptr<Cyprium::VertexArray> m_VertexArray;

	std::shared_ptr<Cyprium::Shader> m_BlueShader;
	std::shared_ptr<Cyprium::VertexArray> m_SquareVA;

	Cyprium::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Cyprium::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Cyprium::Application* Cyprium::CreateApplication()
{
	return new Sandbox();
}