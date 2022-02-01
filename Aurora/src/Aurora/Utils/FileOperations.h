#pragma once

namespace Aurora
{
	enum PathType
	{
		ModelPath,
		ImagePath,
		TexturePath,
		ShaderPath,
		AssetPath
	};

	class FilesManager
	{
	public:
		static std::map<int,std::vector<std::string>> Paths;
	public:
		//Returns the path to the file name provided
		static std::string GetPath(std::string FileName,PathType type);

		//Finds the file in the given directory
		static std::string Find(std::string FileName, std::string directory);

		//Finds the file recursively in the directory
		static std::string FindRecursively(std::string FileName, std::string directory);

		/*
		  Adds path to the map of paths
		  Returns false if the given path is not a directory
		*/
		static bool AddPath(std::string path,PathType type);
	};

}