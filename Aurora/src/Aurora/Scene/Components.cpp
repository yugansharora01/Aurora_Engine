#include "pch.h"
#include "Components.h"
#include "Aurora/High-Level/Model.h"

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

	void TransformComponent::UpdateData(DirectX::XMMATRIX transformMat)
	{
		DirectX::XMVECTOR scaleVec, rotationVec, translationVec;
		DirectX::XMMatrixDecompose(&scaleVec, &rotationVec, &translationVec, transformMat);

		AU_INFO("Rotation {0},{1},{2}", rotation.x, rotation.y, rotation.z);

		DirectX::XMFLOAT4 newRotation, deltaRotation;
		DirectX::XMStoreFloat3(&scale, scaleVec);
		DirectX::XMStoreFloat4(&newRotation, rotationVec);
		DirectX::XMStoreFloat3(&translate, translationVec);

		AU_INFO(" New Rotation {0},{1},{2}", rotation.x, rotation.y, rotation.z);

		deltaRotation.x = DirectX::XMConvertToRadians(newRotation.x) - rotation.x;
		deltaRotation.y = DirectX::XMConvertToRadians(newRotation.y) - rotation.y;
		deltaRotation.z = DirectX::XMConvertToRadians(newRotation.z) - rotation.z;

		rotation.x += deltaRotation.x;
		rotation.y += deltaRotation.y;
		rotation.z += deltaRotation.z;

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
	MeshComponent::MeshComponent()
	{
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}
	MeshComponent::MeshComponent(Ref<VertexShader> VertexShader, Ref<PixelShader> PixelShader, Ref<VertexBuffer> VertexBuffer, Ref<IndexBuffer> IndexBuffer)
		: vShader(VertexShader), pShader(PixelShader), vBuf(VertexBuffer), iBuf(IndexBuffer)
	{
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}

	MeshComponent::MeshComponent(std::string name, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
		:MeshName(name), vShaderPath(vertexShaderPath), pShaderPath(pixelShaderPath)
	{
		model = CreateRef<Model>(MeshName, vShaderPath, pShaderPath);
		IsModel = true;
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}

	MeshComponent::MeshComponent(bool compress, std::string name, std::wstring vertexShaderPath, std::wstring pixelShaderPath)
		:MeshName(name), vShaderPath(vertexShaderPath), pShaderPath(pixelShaderPath)
	{
		model = CreateRef<Model>(MeshName, vShaderPath, pShaderPath,compress);
		IsModel = true;
		color = { 0.146f, 0.574f, 0.578f, 1.0f };
		specularIntensity = 0.6f;
		specularPower = 30.0f;
	}

	void MeshComponent::update()
	{
		if (IsModel)
		{
			auto mesh = model->LoadModel(entity, entity->GetScene());

			if(!mesh->IsEmpty)
			{
				vShader = mesh->vShader;
				pShader = mesh->pShader;
				vBuf = mesh->vBuf;
				iBuf = mesh->iBuf;
			}
			else
			{
				IsEmptyParent = true;
			}
		}
		
	}
}