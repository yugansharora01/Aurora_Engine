#include "pch.h"
#include "FileOperations.h"
#include "Aurora/Core/Log.h"
#include <filesystem>

namespace Aurora
{
	std::map<int, std::vector<std::string>> FilesManager::Paths;

	std::string FilesManager::GetPath(std::string FileName, PathType type)
	{
		if (Paths.empty())
		{
			AddPath(std::filesystem::current_path().string(), PathType::AssetPath);
			AddPath("E:\\Yash\\Aurora\\Aurora-Editor\\assets", PathType::AssetPath);
		}


		//just in case relative path is given
		std::filesystem::path f(FileName);
		auto file = f.filename().string();

		for (auto& paths : Paths[(int)type])
		{
			return Find(file, paths);
		}

		for (auto& paths : Paths[(int)PathType::AssetPath])
		{
			auto p = Find(file, paths);
			if (p.empty())
			{
				AU_INFO("Finding file recursively...");
				p = FindRecursively(file, paths);
			}
			return p;
		}
		
		AU_WARN("Can't Find File : {0}", file);
		return std::string();
	}

	std::string FilesManager::Find(std::string FileName, std::string directory)
	{
		for (auto& p : std::filesystem::directory_iterator(directory))
		{
			if (p.path().filename() == FileName)
			{
				return p.path().string();
			}
		}
		return std::string();
	}

	std::string FilesManager::FindRecursively(std::string FileName,std::string directory)
	{
		for (auto& p : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
		{

			if (p.path().filename() == FileName)
			{
				return p.path().string();
			}
		}
		return std::string();
	}

	bool FilesManager::AddPath(std::string path,PathType type)
	{
		if (!std::filesystem::is_directory(path))
		{
			AU_ERROR("The Path : ", path, " is not a valid directory");
			return false;
		}
		else
		{
			Paths[(int)type].push_back(path);
			return true;
		}
	}
}