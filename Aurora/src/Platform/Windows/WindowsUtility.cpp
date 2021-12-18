#include "pch.h"
#include "Aurora/Utils/PlatformUtil.h"
#include "WindowsUtility.h"

#include "Aurora/Application.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Aurora/Utils/Convertors.h"

#include <commdlg.h>
#include <shobjidl.h>

namespace Aurora {

	std::string FileDialog::OpenFile(const char* filter)
	{
		/*OPENFILENAME ofn;
		char szFile[260] = { 0 };
		ZeroMemory(&ofn,sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = std::dynamic_pointer_cast<WindowsWindow>(Application::Get().GetWindowptr())->GetWin32WindowPtr()->GetHandle();
		ofn.lpstrFile = szFile;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = 0;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileName(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}

		return std::string();*/

		std::string str;

		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							std::wstring ws(pszFilePath);
							str = ws2s(ws);
							MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
		return str;
	}

	std::string FileDialog::SaveFile(const char* filter)
	{
		/*OPENFILENAME ofn;
		char szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = std::dynamic_pointer_cast<WindowsWindow>(Application::Get().GetWindowptr())->GetWin32WindowPtr()->GetHandle();
		ofn.lpstrFile = szFile;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}

		return std::string();*/


		std::string str;

		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{
			IFileSaveDialog* pFileSave;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
				IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileSave->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileSave->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							std::wstring ws(pszFilePath);
							str = ws2s(ws);
							MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileSave->Release();
			}
			CoUninitialize();
		}
		return str;
	}


}
	



	//std::vector<int> WinGetDisplayCoord()
	//{
	//	auto wnd = (Win32_Window*)Application::Get().GetWindow().GetNativeWindowPtr();
	//	HWND hwnd = wnd->GetHandle();


	//	RECT rect;

	//	GetWindowRect(hwnd, &rect);

	//	RECT wrect;
	//	GetWindowRect(hwnd, &wrect);
	//	RECT crect;
	//	GetClientRect(hwnd, &crect);
	//	POINT lefttop = { crect.left, crect.top }; // Practicaly both are 0
	//	ClientToScreen(hwnd, &lefttop);
	//	POINT rightbottom = { crect.right, crect.bottom };
	//	ClientToScreen(hwnd, &rightbottom);

	//	int left_border = lefttop.x - wrect.left; // Windows 10: includes transparent part
	//	int right_border = wrect.right - rightbottom.x; // As above
	//	int bottom_border = wrect.bottom - rightbottom.y; // As above
	//	int top_border_with_title_bar = lefttop.y - wrect.top; // There is no transparent part

	//	std::vector<int> vec = { rect.left + left_border, rect.top + top_border_with_title_bar ,rect.right - right_border ,rect.bottom - bottom_border };
	//	return vec;

	//}