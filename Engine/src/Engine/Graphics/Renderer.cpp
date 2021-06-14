#include "ltpch.h"
#include "Renderer.h"

#include "GraphicsContext.h"

#include "RenderCommand.h"

namespace Light {

	Renderer* Renderer::s_Context;

	Renderer::Renderer(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext)
		: m_RenderCommand(renderCommand), m_SharedContext(sharedContext)
	{
		s_Context = this;

		// QUADRENDERER //
		m_QuadRenderer.shader = std::unique_ptr<Shader>(Shader::Create("res/vertex.vertex", "res/fragment.fragment", m_SharedContext));
		m_QuadRenderer.vertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(QuadRendererProgram::QuadVertexData), LT_MAX_QUAD * 4, m_SharedContext));
		m_QuadRenderer.vertexLayout = std::unique_ptr<VertexLayout>(VertexLayout::Create(m_QuadRenderer.vertexBuffer.get(), m_QuadRenderer.shader.get(), { { "POSITION", VertexElementType::Float3 },{ "COLOR", VertexElementType::Float4 } }, m_SharedContext));
		m_QuadRenderer.indexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(nullptr, LT_MAX_QUAD * 3, m_SharedContext));
		// QUADRENDERER //
	}

	Renderer* Renderer::Create(std::shared_ptr<RenderCommand> renderCommand, void* sharedContext)
	{
		return new Renderer(renderCommand, sharedContext);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		s_Context->DrawQuadImpl(position, size, tint);
	}

	void Renderer::DrawQuadImpl(const glm::vec3& position, const glm::vec2& size, const glm::vec4& tint)
	{
		// check
		if (m_QuadRenderer.mapCurrent + 4 >= m_QuadRenderer.mapEnd)
		{
			LT_ENGINE_WARN("Render::DrawQuad: max calls per frame exceeded the limit: {}", LT_MAX_QUAD);

			EndScene();
			m_QuadRenderer.Map();
		}

		// locals
		const float xMin = position.x;
		const float yMin = position.y;
		const float xMax = position.x + size.x;
		const float yMax = position.y + size.y;

		// TOP LEFT
		m_QuadRenderer.mapCurrent->position = { xMin, yMin, position.z };
		m_QuadRenderer.mapCurrent->tint = glm::vec4(1.0f, 0.1f, 0.1f, 1.0f);
		m_QuadRenderer.mapCurrent++;

		// TOP RIGHT
		m_QuadRenderer.mapCurrent->position = { xMax, yMin, position.z };
		m_QuadRenderer.mapCurrent->tint = glm::vec4(0.1f, 1.0f, 0.1f, 1.0f);
		m_QuadRenderer.mapCurrent++;

		// BOTTOM RIGHT
		m_QuadRenderer.mapCurrent->position = { xMax, yMax, position.z };
		m_QuadRenderer.mapCurrent->tint = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
		m_QuadRenderer.mapCurrent++;

		// BOTTOM LEFT
		m_QuadRenderer.mapCurrent->position = { xMin, yMax, position.z };
		m_QuadRenderer.mapCurrent->tint = glm::vec4(0.1f, 0.1f, 1.0f, 1.0f);
		m_QuadRenderer.mapCurrent++;

		// advance
		m_QuadRenderer.quadCount++;
	}


	void Renderer::BeginScene()
	{
		m_QuadRenderer.Map();
	}

	void Renderer::EndScene()
	{
		m_QuadRenderer.Bind();
		m_RenderCommand->DrawIndexed(m_QuadRenderer.quadCount * 6);
		m_QuadRenderer.quadCount = 0;
	}

}