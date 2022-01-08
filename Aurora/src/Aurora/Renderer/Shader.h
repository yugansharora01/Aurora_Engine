#pragma once

#include <DirectXMath.h>
#include <d3d11.h>


namespace Aurora {

	struct Data
	{
		unsigned int id;
		std::vector<DirectX::XMFLOAT4> data;
		Data() = default;
	};

	class Shader
	{
	public:

		virtual void UploadData(void* val, size_t SizeOfEle, size_t SizeOfData,bool StoreData = true ,int slot = -1) = 0;

		virtual void UploadFloat(std::vector<float> vec, bool StoreData = true, int slot = -1) = 0;

		virtual void UploadFloat2(std::vector<DirectX::XMFLOAT2> vec2, bool StoreData = true, int slot = -1) = 0;

		virtual void UploadFloat3(std::vector<DirectX::XMFLOAT3> vec3, bool StoreData = true, int slot = -1) = 0;

		virtual void UploadFloat4(std::vector<DirectX::XMFLOAT4> vec4, bool StoreData = true, int slot = -1) = 0;

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void Refresh() = 0;
	};

	class PixelShader : public Shader
	{
	public:
		std::string path;

		std::vector<std::vector<DirectX::XMFLOAT4>> UploadedData;
	public:
		virtual ~PixelShader() = default;
		static std::shared_ptr<PixelShader> Create(const std::wstring& path);
		virtual void SetDataToAppend(unsigned int Elements, unsigned int EleSize, void* data) = 0;
		virtual void* GetAppendedData() = 0;
	};

	class VertexShader : public Shader
	{
	public:
		std::string path;

		std::vector<std::vector<DirectX::XMFLOAT4>> UploadedData;
	public:
		virtual ~VertexShader() = default;

		virtual ID3DBlob* GetBytecode() const noexcept = 0;
		static std::shared_ptr<VertexShader> Create(const std::wstring& path);
	};

}