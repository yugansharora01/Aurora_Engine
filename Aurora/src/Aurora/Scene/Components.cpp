#include "pch.h"
#include "Components.h"
#include "Aurora/Models/Model.h"
#include "Aurora/Utils/FileOperations.h"
#include "Aurora/Models/Light.h"

namespace Aurora {
	TransformComponent::TransformComponent()
	{
		translate = DirectX::XMFLOAT3(-4.0f, 0.0f, 20.0f);
		rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	}

	void TransformComponent::update()
	{

		DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)*
			DirectX::XMMatrixTranslation(translate.x, translate.y, translate.z)*
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	}

	DirectX::XMMATRIX TransformComponent::GetTransform()
	{
		DirectX::XMFLOAT4 zero(0.0f, 0.0f, 0.0f, 1.0f);
		DirectX::XMFLOAT4 identity(1.0f, 0.0f, 0.0f, 0.0f);
		auto zeroVec = DirectX::XMLoadFloat4(&zero);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto identityQuat = DirectX::XMLoadFloat4(&identity);

		transform = DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);

		return transform;
	}

	
	LightComponent::LightComponent()
	{
		ambient = { 0.15f, 0.15f, 0.15f,1.0f };
		diffuseColor = { 1.0f,1.0f,1.0f,1.0f };
		diffuseIntensity = 1.0f;
		attConst = 1.0f;
		attLin = 0.045f;
		attQuad = 0.0075f;
	}

	LightComponent::~LightComponent()
	{
		auto scene = entity->GetScene();
		scene->RemoveLight(entity);
	}

	void LightComponent::OnComponentAdd()
	{
		auto scene = entity->GetScene();
		/*LightInfo info;
		info.ambient = ambient;
		info.diffuseColor = diffuseColor ;
		info.diffuseIntensity = diffuseIntensity;
		info.attConst = attConst;
		info.attLin = attLin;
		info.attQuad = attQuad;
		info.type = LightType::Point;*/
		scene->AddLight(entity);
	}

	MeshComponent::MeshComponent()
	{
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}
	

	MeshComponent::MeshComponent(std::string name)
		:MeshName(name)
	{
		IsModel = true;
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}

	MeshComponent::MeshComponent(bool compress, std::string name)
		:MeshName(name)
	{
		IsModel = true;
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}

	void MeshComponent::update()
	{
		//if (IsModel)
		//{
		//	//auto mesh = model->LoadModel(entity, entity->GetScene());

		//	if(!mesh->IsEmpty)
		//	{
		//		vShader = mesh->vShader;
		//		pShader = mesh->pShader;
		//		vBuf = mesh->vBuf;
		//		iBuf = mesh->iBuf;
		//	}
		//	else
		//	{
		//		IsEmptyParent = true;
		//	}
		//}
		
	}
	void MeshComponent::SetTexture(std::string Path)
	{
		auto str = FilesManager::GetPath(Path,PathType::TexturePath);
		IsTextured = true;
		this->path = Path;
		//texture = Texture::Create(str);
	}
}