#pragma once
#include "ECS.h"
#include "Aurora/Renderer/BindableBase.h"
#include <glm/glm.hpp>

namespace Aurora {
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
		glm::vec3 transform;
		glm::vec3 rotation;
		glm::vec3 scale;
	public:
		TransformComponent()
		{
			transform = glm::vec3({ -4.0f,0.0f,20.0f });
			rotation = glm::vec3({ 0.0f,0.0f,0.0f });
			scale = glm::vec3({ 1.0f,1.0f,1.0f });
		}
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::vec3 Transform, glm::vec3 Rotation, glm::vec3 Scale)
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