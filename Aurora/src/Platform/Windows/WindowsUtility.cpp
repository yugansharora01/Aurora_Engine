#include "pch.h"
#include "Aurora/Utils/PlatformUtil.h"
#include "WindowsUtility.h"

#include "Aurora/Application.h"
#include "Platform/Windows/WindowsWindow.h"

#include <commdlg.h>

namespace Aurora {

	std::string FileDialog::OpenFile(const char* filter)
	{
		OPENFILENAME ofn;

		CHAR szFile[260] = { 0 };

		CHAR currentDir[256] = { 0 };

		ZeroMemory(&ofn, sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME); 
		ofn.hwndOwner = std::dynamic_pointer_cast<WindowsWindow>(Application::Get().GetWindowptr())->GetWin32WindowPtr()->GetHandle();

		ofn.lpstrFile = szFile; 
		ofn.nMaxFile = sizeof(szFile);

		if (GetCurrentDirectoryA(256, currentDir)) 
			ofn.lpstrInitialDir = currentDir;

		ofn.lpstrFilter = filter;

		ofn.nFilterIndex = 1;

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileName(&ofn) == TRUE) 
			return ofn.lpstrFile;

		return std::string();

	}

	std::string FileDialog::SaveFile(const char* filter)
	{
		OPENFILENAME ofn;

		CHAR szFile[260] = { 0 };

		CHAR currentDir[256] = { 0 };

		ZeroMemory(&ofn, sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = std::dynamic_pointer_cast<WindowsWindow>(Application::Get().GetWindowptr())->GetWin32WindowPtr()->GetHandle();

		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);

		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;

		ofn.lpstrFilter = filter;

		ofn.nFilterIndex = 1;

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetSaveFileName(&ofn) == TRUE)
		{
			std::string Retstr(ofn.lpstrFile);
			return Retstr + ".Aurora";
		}

		return std::string();

	}
}