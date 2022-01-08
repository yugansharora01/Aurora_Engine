#include "pch.h"
#include "DirectXHelperFunc.h"

namespace Aurora
{
	HRESULT CompileShader(std::wstring srcFile, std::string entryPoint, std::string profile, ID3DBlob** blob)
	{

		*blob = nullptr;

		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( AU_DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif

		const D3D_SHADER_MACRO defines[] =
		{
			NULL, NULL
		};

		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(srcFile.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entryPoint.c_str(), profile.c_str(),
			flags, 0, &shaderBlob, &errorBlob);
		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}

			if (shaderBlob)
				shaderBlob->Release();

			return hr;
		}

		*blob = shaderBlob;

		return hr;
	}


	DXGI_FORMAT GetPropertiesFormat(bool IsNormalised, PropertiesDataType type, unsigned int NumberOfBits)
	{
		if (IsNormalised)
		{
			if (type == PropertiesDataType::Uint)
			{
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_UNORM; break;
				case 16: return DXGI_FORMAT_R16_UNORM; break;
				}
			}
			else {
				if (type == PropertiesDataType::Sint)
				{
					switch (NumberOfBits)
					{
					case 8:  return DXGI_FORMAT_R8_SNORM; break;
					case 16: return DXGI_FORMAT_R16_SNORM; break;
					}
				}
			}
		}
		else {


			switch (type)
			{
			case PropertiesDataType::Float:
				switch (NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16_FLOAT;
				case 32: return DXGI_FORMAT_R32_FLOAT;
				}
				break;
			case PropertiesDataType::Float2:
				switch (NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16G16_FLOAT;
				case 32: return DXGI_FORMAT_R32G32_FLOAT;
				}
				break;
			case PropertiesDataType::Float3:
				return DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case PropertiesDataType::Float4:
				switch (NumberOfBits)
				{
				case 16: return DXGI_FORMAT_R16G16B16A16_FLOAT;
				case 32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
				break;
			case PropertiesDataType::Uint:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_UINT;
				case 16: return DXGI_FORMAT_R16_UINT;
				case 32: return DXGI_FORMAT_R32_UINT;
				}
				break;
			case PropertiesDataType::Uint2:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8_UINT;
				case 16: return DXGI_FORMAT_R16G16_UINT;
				case 32: return DXGI_FORMAT_R32G32_UINT;
				}
				break;
			case PropertiesDataType::Uint3:

				return DXGI_FORMAT_R32G32B32_UINT;
				break;
			case PropertiesDataType::Uint4:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_UINT;
				case 16: return DXGI_FORMAT_R16G16B16A16_UINT;
				case 32: return DXGI_FORMAT_R32G32B32A32_UINT;
				}
				break;
			case PropertiesDataType::Sint:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8_SINT;
				case 16: return DXGI_FORMAT_R16_SINT;
				case 32: return DXGI_FORMAT_R32_SINT;
				}
				break;
			case PropertiesDataType::Sint2:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8_SINT;
				case 16: return DXGI_FORMAT_R16G16_SINT;
				case 32: return DXGI_FORMAT_R32G32_SINT;
				}
				break;
			case PropertiesDataType::Sint3:
				return DXGI_FORMAT_R32G32B32_SINT;
				break;
			case PropertiesDataType::Sint4:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_SINT;
				case 16: return DXGI_FORMAT_R16G16B16A16_SINT;
				case 32: return DXGI_FORMAT_R32G32B32A32_SINT;
				}
				break;
			case PropertiesDataType::Unorm:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_UNORM;
				case 16: return DXGI_FORMAT_R16G16B16A16_UNORM;
				}
				break;
			default:
				switch (NumberOfBits)
				{
				case 8:  return DXGI_FORMAT_R8G8B8A8_TYPELESS;
				case 16: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
				case 32: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
				}
				break;
			}
		}
	}
}