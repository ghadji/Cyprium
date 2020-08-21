#include <Cyprium.h>

#include "imgui/imgui.h"
#include <glm\glm\ext\matrix_transform.hpp>
#include <Platform\OpenGL\OpenGLShader.h>
#include <glm\glm\gtc\type_ptr.hpp>

class ExampleLayer : public Cyprium::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
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

		m_Shader = Cyprium::Shader::Create("assets/shaders/SimpleShader.glsl");

		m_FlatColorShader = Cyprium::Shader::Create("assets/shaders/FlatColorTexture.glsl");

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = Cyprium::Texture2D::Create("assets/textures/Checkerboard.png");
		m_HlmiLogoTexture = Cyprium::Texture2D::Create("assets/textures/Halloumination.png");

		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Cyprium::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Cyprium::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Cyprium::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cyprium::RenderCommand::Clear();

		Cyprium::Renderer::BeginScene(m_CameraController.GetCamera());

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

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Cyprium::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_HlmiLogoTexture->Bind();
		Cyprium::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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

	void OnEvent(Cyprium::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Cyprium::ShaderLibrary m_ShaderLibrary;
	Cyprium::Ref<Cyprium::Shader> m_Shader;
	Cyprium::Ref<Cyprium::VertexArray> m_VertexArray;

	Cyprium::Ref<Cyprium::Shader> m_FlatColorShader;
	Cyprium::Ref<Cyprium::VertexArray> m_SquareVA;

	Cyprium::Ref<Cyprium::Texture2D> m_Texture, m_HlmiLogoTexture;

	Cyprium::OrthographicCameraController m_CameraController;
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