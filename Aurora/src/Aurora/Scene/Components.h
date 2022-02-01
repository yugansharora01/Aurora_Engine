#pragma once
#include "ECS.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Aurora/Core/AuroraMath.h"
#include "Aurora/Core/Log.h"
#include "Aurora/Renderer/Texture.h"

#include <DirectXMath.h>

namespace Aurora {
	class Model;

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
		~TagComponent() = default;
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
		TransformComponent();

		TransformComponent(const TransformComponent&) = default;

		TransformComponent(DirectX::XMFLOAT3 Translate)
			:translate(Translate)
		{
			rotation = DirectX::XMFLOAT3();
			scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TransformComponent(DirectX::XMFLOAT3 Translate, DirectX::XMFLOAT3 Rotation, DirectX::XMFLOAT3 Scale)
			:translate(Translate), rotation(Rotation), scale(Scale) {}

		~TransformComponent() = default;


		virtual void update() override;

		DirectX::XMMATRIX GetTransform();
		
		
	};

	class MeshComponent : public Component
	{
	public:

		DirectX::XMFLOAT4 color;
		float specularIntensity;
		float specularPower;

		std::string MeshName;

		bool IsModel = false;
		bool IsEmptyParent = false;
		bool IsTextured = false;

		std::string path;

	public:
		MeshComponent();
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(std::string MeshName);
		MeshComponent(bool compress,std::string MeshName);
		~MeshComponent() = default;
		virtual void update() override;
		void SetTexture(std::string path);
	};

	class LightComponent : public Component
	{
	public:
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	public:
		LightComponent();
		LightComponent(const LightComponent&) = default;
		~LightComponent();
		virtual void OnComponentAdd() override;
		virtual void update() override {}
	};
}