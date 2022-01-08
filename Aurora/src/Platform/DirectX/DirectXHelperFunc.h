#pragma once
#include <dxgiformat.h>
#include "Aurora/Renderer/Buffer.h"

namespace Aurora
{
	HRESULT CompileShader(std::wstring srcFile, std::string entryPoint, std::string profile, ID3DBlob** blob);
	DXGI_FORMAT GetPropertiesFormat(bool IsNormalised, PropertiesDataType type, unsigned int NumberOfBits);
}