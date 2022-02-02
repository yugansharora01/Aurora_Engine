#pragma once

#include "BindableBase.h"
#include "Aurora/Models/Model.h"

namespace Aurora 
{
	class Camera;
	class Light;
	class D3D11PixelConstantBuffer;
	class D3D11VertexConstantBuffer;

	class ModelTexture
	{
	public:
		enum TextureType
		{
			Albedo,
			Diffuse,
			Specular
		};

		std::map<TextureType, std::string> Textures;

		void AddTexture(std::string tex, TextureType type);
		bool HaveTex(TextureType type);
		std::string GetTex(TextureType type);
	};

	struct ModelProperties
	{
		Ref<VertexShader> vshader;
		Ref<PixelShader> pshader;
		ModelTexture Textures;
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 origin;
		std::vector<DirectX::XMFLOAT4> MiscelData;
	};

	struct ModelData
	{
		unsigned int count;
		Ref<VertexBuffer> vbuf; 
		Ref<IndexBuffer> ibuf; 
		Ref<VertexShader> vshader; 
		Ref<PixelShader> pshader;
		ModelTexture Textures;

		DirectX::XMMATRIX mat;

		std::vector<DirectX::XMFLOAT4> MiscelData;
	};

	class RenderQueue
	{
	public:
		std::unordered_map<std::string, ModelData> Models;
		
	public:
		RenderQueue() = default;
		void submit(std::string ModelPath,ModelProperties ModelProp);
	};
	
	class Renderer
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(Ref<Camera> camera,std::vector<Light> lights);
		static void EndScene();

		static void Bind(ModelData modelData);
		static void SetData(ModelData modelData);
		static void DrawModel(std::string ModelName, ModelProperties ModelProp);
		
	private:
		static std::vector<std::string> ModelPaths;
		static RenderQueue s_queue;
		static bool hasLights;
		static std::vector<DirectX::XMFLOAT4> data;
		static Ref<D3D11PixelConstantBuffer> pConst;
		static Ref<D3D11VertexConstantBuffer> vConst;
		static DirectX::XMMATRIX ViewMat;
		static DirectX::XMMATRIX ProjMat;
	};

}