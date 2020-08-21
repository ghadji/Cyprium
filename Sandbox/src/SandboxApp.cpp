#include <Cyprium.h>

#include "imgui/imgui.h"
#include <glm\glm\ext\matrix_transform.hpp>
#include <Platform\OpenGL\OpenGLShader.h>
#include <glm\glm\gtc\type_ptr.hpp>

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

		Cyprium::Ref<Cyprium::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cyprium::VertexBuffer::Create(vertices, sizeof(vertices)));

		Cyprium::BufferLayout layout = {
			{ Cyprium::ShaderDataType::Float3, "a_Position" },
			{ Cyprium::ShaderDataType::Float4, "a_Color" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Cyprium::Ref<Cyprium::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cyprium::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Cyprium::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Cyprium::Ref<Cyprium::VertexBuffer> squareVB;
		squareVB.reset(Cyprium::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Cyprium::ShaderDataType::Float3, "a_Position" },
			{ Cyprium::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Cyprium::Ref<Cyprium::IndexBuffer> squareIB;
		squareIB.reset(Cyprium::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_Shader.reset(Cyprium::Shader::Create("assets/shaders/SimpleShader.glsl"));

		m_FlatColorShader.reset(Cyprium::Shader::Create("assets/shaders/FlatColorTexture.glsl"));

		m_TextureShader.reset(Cyprium::Shader::Create("assets/shaders/Texture.glsl"));
		
		m_Texture = Cyprium::Texture2D::Create("assets/textures/Checkerboard.png");
		m_HlmiLogoTexture = Cyprium::Texture2D::Create("assets/textures/Halloumination.png");

		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Cyprium::Timestep ts) override
	{

		// Camera movement X axis
		if (Cyprium::Input::IsKeyPressed(CP_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		// Camera movement Y axis
		if (Cyprium::Input::IsKeyPressed(CP_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		// Camera Rotation
		if (Cyprium::Input::IsKeyPressed(CP_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Cyprium::Input::IsKeyPressed(CP_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Cyprium::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cyprium::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cyprium::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		
		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Cyprium::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		m_Texture->Bind();
		Cyprium::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_HlmiLogoTexture->Bind();
		Cyprium::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle rendering
		//Cyprium::Renderer::Submit(m_VertexArray, m_Shader); 

		Cyprium::Renderer::EndScene();
	}
	
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Cyprium::Event& event) override
	{

	}
private:
	Cyprium::Ref<Cyprium::Shader> m_Shader;
	Cyprium::Ref<Cyprium::VertexArray> m_VertexArray;

	Cyprium::Ref<Cyprium::Shader> m_FlatColorShader, m_TextureShader;
	Cyprium::Ref<Cyprium::VertexArray> m_SquareVA;

	Cyprium::Ref<Cyprium::Texture2D> m_Texture, m_HlmiLogoTexture;

	Cyprium::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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