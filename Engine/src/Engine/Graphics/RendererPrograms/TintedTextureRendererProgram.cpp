#include "ltpch.h"
#include "TintedTextureRendererProgram.h"

#include "Camera/Camera.h"

#include "Graphics/Shader.h"
#include "Graphics/Buffers.h"
#include "Graphics/VertexLayout.h"

#include "Utility/ResourceManager.h"

namespace Light {

	TintedTextureRendererProgram::TintedTextureRendererProgram(unsigned int maxVertices, Ref<SharedContext> sharedContext)
		: m_Shader(nullptr),
		  m_IndexBuffer(nullptr),
		  m_VertexLayout(nullptr),
		  m_MapCurrent(nullptr),
		  m_MapEnd(nullptr),
		  m_QuadCount(0u),
		  m_MaxVertices(maxVertices)
	{
		// #todo: don't use relative path
		ResourceManager::LoadShader("LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER", "../Engine/res/Shaders/TintedTexture/TintedTexture_VS", "../Engine/res/Shaders/TintedTexture/TintedTexture_PS");

		m_Shader = ResourceManager::GetShader("LT_ENGINE_RESOURCES_TINTED_TEXTURE_SHADER");
		m_VertexBuffer = Ref<VertexBuffer>(VertexBuffer::Create(nullptr, sizeof(TintedTextureVertexData), maxVertices, sharedContext));
		m_IndexBuffer = Ref<IndexBuffer>(IndexBuffer::Create(nullptr, (maxVertices / 4) * 6, sharedContext));
		m_VertexLayout = Ref<VertexLayout>(VertexLayout::Create(m_VertexBuffer, m_Shader, { { "POSITION", VertexElementType::Float4 },
		                                                                                    { "TINT"    , VertexElementType::Float4 },
		                                                                                    { "TEXCOORD", VertexElementType::Float2 }}, sharedContext));
	}

	bool TintedTextureRendererProgram::Advance()
	{
		if (m_MapCurrent + 4 >= m_MapEnd)
		{
			LT_ENGINE_WARN("TintedTextureRendererProgram::Advance: 'VertexBuffer' map went beyond 'MaxVertices': {}", m_MaxVertices);
			return false;
		}

		m_MapCurrent += 4;
		m_QuadCount++;
		return true;
	}

	void TintedTextureRendererProgram::Map()
	{
		m_QuadCount = 0u;

		m_MapCurrent = (TintedTextureRendererProgram::TintedTextureVertexData*)m_VertexBuffer->Map();
		m_MapEnd = m_MapCurrent + m_MaxVertices;
	}

	void TintedTextureRendererProgram::UnMap()
	{
		m_VertexBuffer->UnMap();
	}

	void TintedTextureRendererProgram::Bind()
	{
		m_Shader->Bind();
		m_VertexLayout->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();
	}

}