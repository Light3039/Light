#include "ltpch.h"
#include "dxBuffers.h"

#include "dxSharedContext.h"

namespace Light {

	dxConstantBuffer::dxConstantBuffer(ConstantBufferIndex index, unsigned int size, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext), m_Index((int)index)
	{
		D3D11_BUFFER_DESC bufferDesc = { };
		
		bufferDesc.ByteWidth = size;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateBuffer(&bufferDesc, nullptr, &m_Buffer));
		m_Context->GetDeviceContext()->VSSetConstantBuffers(m_Index, 1u, m_Buffer.GetAddressOf());
	}

	void dxConstantBuffer::Bind()
	{
		m_Context->GetDeviceContext()->VSSetConstantBuffers(m_Index, 1u, m_Buffer.GetAddressOf());
	}

	void* dxConstantBuffer::Map()
	{
		m_Context->GetDeviceContext()->VSSetConstantBuffers(m_Index, 1u, m_Buffer.GetAddressOf());
		m_Context->GetDeviceContext()->Map(m_Buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_Map);
		return m_Map.pData;
	}

	void dxConstantBuffer::UnMap()
	{
		m_Context->GetDeviceContext()->Unmap(m_Buffer.Get(), NULL);
	}

	//* VERTEX_BUFFER *//
	dxVertexBuffer::dxVertexBuffer(float* vertices, unsigned int stride, unsigned int count, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Stride(stride), m_Context(sharedContext)
	{
		// buffer desc
		D3D11_BUFFER_DESC bd = { 0 };

		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		bd.ByteWidth = count * stride;
		bd.StructureByteStride = stride;

		// create buffer
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateBuffer(&bd, nullptr, &m_Buffer));
	}

	dxVertexBuffer::~dxVertexBuffer()
	{
		UnBind();
	}

	void* dxVertexBuffer::Map()
	{
		m_Context->GetDeviceContext()->Map(m_Buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_Map);
		return m_Map.pData;
	}

	void dxVertexBuffer::UnMap()
	{
		m_Context->GetDeviceContext()->Unmap(m_Buffer.Get(), NULL);
	}

	void dxVertexBuffer::Bind()
	{
		static const unsigned int offset = 0u;
		m_Context->GetDeviceContext()->IASetVertexBuffers(0u, 1u, m_Buffer.GetAddressOf(), &m_Stride, &offset);
	}

	void dxVertexBuffer::UnBind()
	{
		static const unsigned int offset = 0u;
		static ID3D11Buffer* buffer = nullptr;

		m_Context->GetDeviceContext()->IASetVertexBuffers(0u, 1u, &buffer, &m_Stride, &offset);
	}

	//* INDEX_BUFFER *//
	dxIndexBuffer::dxIndexBuffer(unsigned int* indices, unsigned int count, std::shared_ptr<dxSharedContext> sharedContext)
		: m_Context(sharedContext)
	{
		// generate indices if not provided
		bool hasIndices = !!indices;
		if (!hasIndices)
		{
			// check
			if (count % 6 != 0)
			{
				LT_ENGINE_WARN("dxIndexBuffer::dxIndexBuffer: 'indices' can only be null if count is multiple of 6");
				LT_ENGINE_WARN("dxIndexBuffer::dxIndexBuffer: adding {} to 'count' -> {}", (6 - (count % 6)), count + (6 - (count % 6)));
				count = count + (6 - (count % 6));
			}

			// create indices
			indices = new unsigned int[count];
			unsigned int offset = 0;
			for (unsigned int i = 0; i < count; i += 6)
			{
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 3;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 1;
				indices[i + 5] = offset + 0;

				offset += 4;
			}
		}

		// buffer desc
		D3D11_BUFFER_DESC bd = { 0 };
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;

		bd.ByteWidth = count * sizeof(unsigned int);
		bd.StructureByteStride = sizeof(unsigned int);

		// subresource data
		D3D11_SUBRESOURCE_DATA sd = { 0 };
		sd.pSysMem = indices;

		// create buffer
		HRESULT hr;
		DXC(m_Context->GetDevice()->CreateBuffer(&bd, &sd, &m_Buffer));

		// delete indices
		if (!hasIndices)
			delete[] indices;
	}

	dxIndexBuffer::~dxIndexBuffer()
	{
		UnBind();
	}

	void dxIndexBuffer::Bind()
	{
		m_Context->GetDeviceContext()->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	}

	void dxIndexBuffer::UnBind()
	{
		static const unsigned int offset = 0u;
		static ID3D11Buffer* buffer = nullptr;

		m_Context->GetDeviceContext()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, offset);
	}

}