#pragma once

#include "AuroraWin.h"

#include <wrl.h>
#include <vector>
#include <dxgidebug.h>
#include <string>

namespace Aurora {

	class DxgiInfoManager
	{
	public:
		DxgiInfoManager();
		~DxgiInfoManager() = default;
		DxgiInfoManager(const DxgiInfoManager&) = default;
		DxgiInfoManager& operator=(const DxgiInfoManager&) = default;
		void Set() noexcept;
		std::vector<std::string> GetMessages() const;
	private:
		unsigned long long next = 0u;
		Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
	};
}