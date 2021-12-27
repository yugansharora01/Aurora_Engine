#pragma once
#include "ECS.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Aurora/AuroraMath.h"
#include "Aurora/Log.h"
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
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 origin; //To Do
		DirectX::XMMATRIX transform;
	public:
		TransformComponent()
		{
			translate = DirectX::XMFLOAT3( -4.0f,0.0f,20.0f );
			rotation = DirectX::XMFLOAT3( 0.0f,0.0f,0.0f );
			scale = DirectX::XMFLOAT3( 1.0f,1.0f,1.0f );
		}

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(DirectX::XMFLOAT3 Translate)
			:translate(Translate)
		{
			rotation = DirectX::XMFLOAT3();
			scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TransformComponent(DirectX::XMFLOAT3 Translate, DirectX::XMFLOAT3 Rotation, DirectX::XMFLOAT3 Scale)
			:translate(Translate), rotation(Rotation), scale(Scale) {}

		~TransformComponent() {}

		virtual void OnComponentAdd() override {}

		virtual void update() override {
		
			DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)*
				DirectX::XMMatrixTranslation(translate.x, translate.y, translate.z)*
				DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		}

		DirectX::XMMATRIX GetTransform()
		{
			return transform;
		}
		
		void UpdateData(DirectX::XMMATRIX transformMat)
		{
			transform = transformMat;
			DirectX::XMVECTOR scaleVec, rotationVec, translationVec;
			DirectX::XMMatrixDecompose(&scaleVec, &rotationVec, &translationVec, transformMat);

			DirectX::XMFLOAT3 newRotation,deltaRotation;
			DirectX::XMStoreFloat3(&scale, scaleVec);
			DirectX::XMStoreFloat3(&newRotation, rotationVec);
			DirectX::XMStoreFloat3(&translate, translationVec);

			deltaRotation.x = newRotation.x - rotation.x;
			deltaRotation.y = newRotation.y - rotation.y;
			deltaRotation.z = newRotation.z - rotation.z;

			AU_INFO("Rotation {0},{1},{2}", rotation.x, rotation.y, rotation.z);
			AU_INFO("New Rotation {0},{1},{2}", newRotation.x, newRotation.y, newRotation.z);

			rotation.x += deltaRotation.x;
			rotation.y += deltaRotation.y;
			rotation.z += deltaRotation.z;

		}
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