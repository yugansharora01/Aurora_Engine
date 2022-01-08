#pragma once

#include "Aurora/Renderer/Buffer.h"

namespace Aurora 
{

	struct RenderTargetProperties
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int NumberOfTargets; //Array Size
		struct RenderTargetFormat
		{
			bool IsNormalised;
			unsigned int NumberOfBits;
			PropertiesDataType type;
		}Format;
		struct DepthFormat
		{
			bool IsNormalised;
			unsigned int NumberOfBits;
			PropertiesDataType type;
		}DepthFormat;
		bool IsCPUAccessable;
		bool IsDataAccessable;

	};

	class RenderTargetManager
	{
	public:
		virtual ~RenderTargetManager() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void* GetTextureAsPointer(std::string str) = 0;
		virtual void* GetTextureData(std::string str) = 0;
		virtual void BindTargets() = 0;
		virtual void RenderToBackBuf() = 0;
		virtual unsigned int GetNumberOfTargets() = 0;

		virtual void AddRenderTarget(std::string str, RenderTargetProperties property) = 0;

		virtual void Clear(float red, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f) = 0;
		
		static std::shared_ptr<RenderTargetManager> Create(unsigned int width, unsigned int height);
	};

}