#pragma once

#include "Aurora/Renderer/Bindables.h"

namespace Aurora {

	class Shader : public Bindables
	{
	public:
		virtual void UploadFloat2(DirectX::XMFLOAT2 val) = 0;
		virtual void UploadFloat3(DirectX::XMFLOAT3 val) = 0;
		virtual void UploadFloat4(DirectX::XMFLOAT4 val) = 0;
		virtual void UploadMat3(DirectX::XMMATRIX mat3) = 0;
		virtual void UploadMat4(DirectX::XMMATRIX mat4) = 0;
		virtual void UploadMat4X8(std::array<DirectX::XMFLOAT4, 8> arr) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class PixelShader : public Shader
	{

		using Bindables::Getgfx;
		using Bindables::GetInfoManager;
	public:
		virtual ~PixelShader() = default;


		static std::shared_ptr<PixelShader> Create(const std::wstring& path);

	};

	class VertexShader : public Shader
	{
	public:
		virtual ~VertexShader() = default;

		virtual ID3DBlob* GetBytecode() const noexcept = 0;
		static std::shared_ptr<VertexShader> Create(const std::wstring& path);
	};

}