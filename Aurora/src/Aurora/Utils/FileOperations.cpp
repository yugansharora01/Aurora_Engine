#include "pch.h"
#include "FileOperations.h"
#include <filesystem>

#include "Aurora/Log.h"

namespace Aurora
{
	std::string Files::GetPath(std::string FileName)
	{
		for (auto& p : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
		{

			if (p.path().filename().string() == FileName)
			{
				return p.path().string();
			}

			AU_INFO(p.path().string());
		}
		return std::string();
	}
}