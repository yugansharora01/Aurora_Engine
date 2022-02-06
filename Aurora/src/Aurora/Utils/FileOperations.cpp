#include "pch.h"
#include "FileOperations.h"
#include "Aurora/Core/Log.h"
#include <filesystem>

namespace Aurora
{
	std::map<int, std::vector<std::string>> FilesManager::Paths;

	void FilesManager::Init()
	{
		AddPath(std::filesystem::current_path().string(), PathType::AssetPath);
		AddPath("E:\\Yash\\Aurora\\Aurora-Editor\\assets", PathType::AssetPath);
		AddPath("E:\\Yash\\Aurora\\Aurora\\src\\Aurora\\Shaders", PathType::ShaderPath);
	}

	std::string FilesManager::GetPath(std::string FileName, PathType type)
	{
		//just in case relative path is given
		std::filesystem::path f(FileName);
		auto file = f.filename().string();

		for (auto& paths : Paths[(int)type])
		{
			auto p = FindRecursively(file, paths);
			if (!p.empty())
			{
				std::filesystem::path path(p);
				AddPath(path.parent_path().string(), type);
				return p;
			}
		}

		for (auto& paths : Paths[(int)PathType::AssetPath])
		{
			auto p = FindRecursively(file, paths);
			if (!p.empty())
			{
				std::filesystem::path path(p);
				AddPath(path.parent_path().string(), type);
				return p;
			}
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
		for (auto& p : std::filesystem::recursive_directory_iterator(directory))
		{
			if (p.path().filename() == FileName)
			{
				return p.path().string();
			}
		}
		return std::string();
	}

	std::string FilesManager::FindDirectory(std::string DirectoryName, std::string StartDirectory)
	{
		for (auto& p : std::filesystem::recursive_directory_iterator(StartDirectory))
		{
			if (p.path().filename() == DirectoryName)
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