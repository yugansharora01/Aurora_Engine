#pragma once
#include "ECS.h"
#include "Aurora/Renderer/BindableBase.h"
#include <DirectXMath.h>

namespace Aurora {

	class IDComponent : public Component
	{
	public:
		UUID ID;
	public:
		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
		IDComponent(const uint64_t id)
			:ID(id) {}
		~IDComponent() {}
	};

	class TagComponent : public Component
	{
	public:
		std::string tag;
	public:
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& str)
			:tag(str){}
		~TagComponent(){}
		virtual void OnComponentAdd() override {}
		virtual void update() override {}
	};

	class TransformComponent : public Component
	{
	public:
		DirectX::XMFLOAT3 transform;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
	public:
		TransformComponent()
		{
			transform = DirectX::XMFLOAT3( -4.0f,0.0f,20.0f );
			rotation = DirectX::XMFLOAT3( 0.0f,0.0f,0.0f );
			scale = DirectX::XMFLOAT3( 1.0f,1.0f,1.0f );
		}

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(DirectX::XMFLOAT3 Transform)
			:transform(Transform) 
		{
			rotation = DirectX::XMFLOAT3();
			scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TransformComponent(DirectX::XMFLOAT3 Transform, DirectX::XMFLOAT3 Rotation, DirectX::XMFLOAT3 Scale)
			:transform(Transform), rotation(Rotation), scale(Scale) {}

		~TransformComponent() {}

		virtual void OnComponentAdd() override {}

		virtual void update() override {}
	};

	class MeshComponent : public Component
	{
	public:
		Ref<VertexShader> vShader;
		Ref<PixelShader> pShader;
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;

		std::vector<DirectX::XMFLOAT4> colors;
	public:
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(Ref<VertexShader> VertexShader, Ref<PixelShader> PixelShader, Ref<VertexBuffer> VertexBuffer, Ref<IndexBuffer> IndexBuffer)
			: vShader(VertexShader), pShader(PixelShader), vBuf(VertexBuffer), iBuf(IndexBuffer) {}
		~MeshComponent() {}
		virtual void OnComponentAdd() override {}
		virtual void update() override {}
	};

}