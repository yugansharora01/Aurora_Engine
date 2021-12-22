#pragma once

//#include "Bindable.h"
#include "Aurora/Renderer/Buffer.h"
#include "Platform/Windows/GraphicsThrowMacros.h"
#include "Aurora/Renderer/Bindables.h"


namespace Aurora {

	class D3D11VertexBuffer : public VertexBuffer , public Bindables
	{
	public:
		D3D11VertexBuffer(const std::vector<VertexData>& vertices);
		
		virtual void Bind() override;
		virtual void Unbind() override{}


		virtual void SetData(void* data, unsigned int size) override;


		virtual void SetLayout(std::vector<LayoutBuffer> layout, std::shared_ptr<class VertexShader> vShader) override;
		virtual void SetTopology(TopologyType type) override;
		
	private:
		UINT stride;
		Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		std::shared_ptr<class D3D11InputLayout> m_layout;
		std::shared_ptr<class D3D11Topology> m_topology;
		Ref<class VertexShader> vertexshader;

		D3D11_BUFFER_DESC bd;
		D3D11_SUBRESOURCE_DATA sd;
	};
}