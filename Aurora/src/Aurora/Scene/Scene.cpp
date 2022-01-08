#include "pch.h"
#include "ECS.h"
#include "Scene.h"
#include "Components.h"
#include "Aurora/Renderer/Renderer.h"
#include "Aurora/Renderer/EditorCamera.h"
#include "Aurora/Application.h"
#include "Aurora/Core/Input.h"

#include "imgui.h"

namespace Aurora {
	struct EntityID
	{
		float id;
	};

	std::vector<DirectX::XMFLOAT4> GetVec(DirectX::XMMATRIX mat)
	{
		std::vector<DirectX::XMFLOAT4> vec;
		DirectX::XMFLOAT4X4 dest;
		DirectX::XMStoreFloat4x4(&dest, mat);
		vec.emplace_back(dest._11, dest._12, dest._13, dest._14);
		vec.emplace_back(dest._21, dest._22, dest._23, dest._24);
		vec.emplace_back(dest._31, dest._32, dest._33, dest._34);
		vec.emplace_back(dest._41, dest._42, dest._43, dest._44);
		return vec;
	}

	Scene::Scene()
	{
		registry = CreateRef<Registry>();
		name = "Untitled";
	}

	Scene::Scene(std::string name)
		:name(name)
	{
		registry = CreateRef<Registry>();
	}

	Ref<Entity> Scene::CreateEntityWithUUID(UUID& id, std::string Name)
	{

		Ref<Entity> entity = CreateRef<Entity>(registry->CreateEntity(), this);
		registry->add(entity);

		if (Name == "")
			Name = "UnNamed";

		entity->AddComponent<IDComponent>(id);
		entity->AddComponent<TagComponent>(Name);
		return entity;
	}

	Ref<Entity> Scene::CreateEntity(std::string Name)
	{
		auto id = UUID();
		return CreateEntityWithUUID(id,Name);
	}

	void Scene::DestroyEntity(Ref<Entity> entity)
	{
		registry->DestroyEntity(entity);
	}

	void Scene::Update(Ref<EditorCamera> Editorcamera, viewportInfo viewport)
	{
		auto height = Application::Get().GetWindow().GetHeight();
		auto width = Application::Get().GetWindow().GetWidth();
		Editorcamera->UpdateProjection( 1, (float)height/ (float)width, 0.5f, 40.0f);
		static bool click = false;

		Renderer::BeginScene();
		auto entities = registry->GetList();
		for (size_t i = 0; i < entities.size(); i++)
		{
			auto& vShader = entities[i]->GetComponent<MeshComponent>()->vShader;
			auto& pShader = entities[i]->GetComponent<MeshComponent>()->pShader;
			auto& vBuf = entities[i]->GetComponent<MeshComponent>()->vBuf;
			auto& iBuf = entities[i]->GetComponent<MeshComponent>()->iBuf;

			vShader->UploadedData.clear();
			vShader->Refresh();
			pShader->Refresh();
			
			pShader->UploadFloat4(pShader->UploadedData[0],false);
			
			auto ViewMat = DirectX::XMMatrixInverse(NULL,Editorcamera->GetTransform());

			auto mat = DirectX::XMMatrixTranspose(
				GetMatrix(entities[i]) * ViewMat * Editorcamera->GetProjection());

			vShader->UploadFloat4(GetVec(mat));
			std::vector<float> vec;
			vec.push_back((float)i);
			vShader->UploadFloat(vec,false);
			
			//------------------------------------------------------------------------------------

			//DirectX::XMFLOAT4 u = { 4.0f,4.0f,4.0f,4.0f };
			//pShader->SetDataToAppend(1u, 16u, &u);
			//std::vector<DirectX::XMINT2> mousecoord = { DirectX::XMINT2((int)x,(int)y) };
			//pShader->UploadData(mousecoord.data(),sizeof(DirectX::XMINT2),mousecoord.size() * sizeof(DirectX::XMINT2), false, 0);
			

			Renderer::Submit(vShader, pShader, vBuf, iBuf);

		}
		Renderer::EndScene();

		if (Input::IsMouseButtonPressed())
			click = true;
		if (!Input::IsMouseButtonPressed())
			click = false;
		float x = -1.0f, y = -1.0f;
		auto w = Application::Get().GetWindow().GetWidth();
		auto h = Application::Get().GetWindow().GetHeight();
		/*if (Input::IsMouseButtonPressed())
		{
			auto [x_, y_] = Input::GetMouseCoord();
			x = x_ - viewport.viewportPos.x;
			y = y_ - viewport.viewportPos.y;
			AU_INFO("mouse coord in viewport space = {0},{1}", x, y);
			x = x / viewport.viewportSize.x;
			y = y / viewport.viewportSize.y;
			AU_INFO(" normalised mouse coord in viewport space = {0},{1}", x, y);
			x = (int)(x * w);
			y = (int)(y * h);
			AU_INFO(" reorganised mouse coord in screen space = {0},{1}", x, y);

			void* data = Application::Get().GetWindow().Gfx()->TargetManager->GetTextureData("Mouse-Pick");
			float* ptr = (float*)data;
			int index = x * y;
			
			float value = ptr[index];
			AU_INFO("value = {0},index = {1}", value, index);
		}*/
		

		/*for (size_t i = 0; i < entities.size(); i++)
		{
			auto& pShader = entities[i]->GetComponent<MeshComponent>()->pShader;
			auto l = pShader->GetAppendedData();
			EntityID f = *(EntityID*)&l;
			AU_INFO("id : {0}", f.id);
		}*/
		
	}

	DirectX::XMMATRIX Scene::GetMatrix(Ref<Entity> entity)
	{
		auto translate = entity->GetComponent<TransformComponent>()->translate;
		auto rotation = entity->GetComponent<TransformComponent>()->rotation;
		auto scale = entity->GetComponent<TransformComponent>()->scale;

		DirectX::XMFLOAT4 zero(0.0f, 0.0f, 0.0f,0.0f);
		DirectX::XMFLOAT4 identity(1.0f, 0.0f, 0.0f,0.0f);
		auto zeroVec = DirectX::XMLoadFloat4(&zero);
		auto translateVec = DirectX::XMLoadFloat3(&translate);
		auto rotationVec = DirectX::XMLoadFloat3(&rotation);
		auto scaleVec = DirectX::XMLoadFloat3(&scale);
		auto identityQuat = DirectX::XMLoadFloat4(&identity);

		return DirectX::XMMatrixTransformation(zeroVec, identityQuat, scaleVec, zeroVec, DirectX::XMQuaternionRotationRollPitchYawFromVector(rotationVec), translateVec);
	}
	
}