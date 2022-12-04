#pragma once

#include "BindableBase.h"
#include "Aurora/Models/Model.h"

namespace Aurora 
{
	class Camera;
	class Light;
	class D3D11PixelConstantBuffer;
	class D3D11VertexConstantBuffer;

	class ShaderManager
	{
	public:
		std::map<std::string, Ref<Shader>> Shaders;
		void AddShader(std::string ShaderName, std::string identifier,Shader::ShaderType type);
		
		Ref<Shader> GetShader(std::string identifier)
		{
			return Shaders[identifier];
		}
	};

	class ModelTexture
	{
	public:
		enum TextureType
		{
			Albedo,
			Diffuse,
			Specular
		};

		std::map<TextureType, std::string> TextureNames;
		static std::map<std::string, Ref<Texture>> Textures;

		void AddTexture(std::string tex, TextureType type);
		void AddTexture(Ref<Texture> texture, std::string identifier);
		bool HaveTex(TextureType type);
		std::string GetTexPath(TextureType type);
		Ref<Texture> GetTex(TextureType type);
		Ref<Texture> GetTex(std::string identifier);
	};

	struct DrawableData
	{
	public:
		unsigned int count;
		std::string ModelName;
		std::string ModelPath;
		Ref<VertexBuffer> vbuf;
		Ref<IndexBuffer> ibuf;
		Ref<Shader> vshader;
		Ref<Shader> pshader;
		bool UsePassedShaders = false;
		ModelTexture Textures;
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 origin;
		DirectX::XMMATRIX mat;
		std::vector<DirectX::XMFLOAT4> MiscelData;
	};

	struct TextData
	{
		unsigned int width;
		unsigned int height;
		std::string Text;
		DirectX::XMFLOAT3 translate;
		DirectX::XMFLOAT3 rotation;
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 origin;
		DirectX::XMMATRIX mat;
		std::vector<DirectX::XMFLOAT4> MiscelData;
	};

	class RenderQueue
	{
	public:
		std::unordered_map<std::string, Ref<Model>> AllModels;
		std::unordered_map<std::string, DrawableData> Models; // TO DO: convert this to vector
		
	public:
		RenderQueue() = default;
		void submit(DrawableData ModelProp);
		void SubmitModel(DrawableData ModelProp);
		void SubmitText(TextData data, DrawableData Prop);
	};
	
	class Renderer
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(Ref<Camera> camera,std::vector<Light> lights);
		static void EndScene();
		static void DrawModel(DrawableData ModelProp);
		static void RenderText(TextData data);

	private:
		static void Bind(DrawableData modelData);
		static void SetData(DrawableData modelData);
		
	private:
		static std::vector<std::string> ModelPaths;
		static RenderQueue s_queue;
		static ShaderManager Manager;
		static bool hasLights;
		static std::vector<DirectX::XMFLOAT4> data;
		static Ref<D3D11PixelConstantBuffer> pConst;
		static Ref<D3D11VertexConstantBuffer> vConst;
		static DirectX::XMMATRIX ViewMat;
		static DirectX::XMMATRIX ProjMat;
	};

}