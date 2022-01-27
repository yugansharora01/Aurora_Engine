#pragma once
#include "ECS.h"
#include "Aurora/Renderer/BindableBase.h"
#include "Aurora/AuroraMath.h"
#include "Aurora/Log.h"
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
		
		void UpdateData(DirectX::XMMATRIX transformMat);
		
		void UpdateData(DirectX::XMFLOAT3 translate, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 scale)
		{
			//TO DO
		}
	};

	class MeshComponent : public Component
	{
	public:
		Ref<VertexShader> vShader;
		Ref<PixelShader> pShader;
		Ref<VertexBuffer> vBuf;
		Ref<IndexBuffer> iBuf;
		Ref<Texture> texture;

		DirectX::XMFLOAT4 color;
		float specularIntensity;
		float specularPower;

		std::string MeshName;
		std::wstring vShaderPath;
		std::wstring pShaderPath;

		bool IsModel = false;
		bool IsEmptyParent = false;
		bool IsTextured = false;

		std::string path;

		Ref<Model> model;
	public:
		MeshComponent();
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(Ref<VertexShader> VertexShader, Ref<PixelShader> PixelShader, Ref<VertexBuffer> VertexBuffer, Ref<IndexBuffer> IndexBuffer);
		MeshComponent(std::string MeshName, std::wstring vShaderPath, std::wstring pShaderPath);
		MeshComponent(bool compress,std::string MeshName, std::wstring vShaderPath, std::wstring pShaderPath);
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
		~LightComponent() = default;
		virtual void update() override {}
	};
}