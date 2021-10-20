#include "stdafx.h"
#include "Path.h"
#include <string.h>
#include "String.h"

// string ���� �־��� path�� wstring���� �ٲ㼭 ����.
// ExistFile�� �ش� ��ο� ������ �����ϴ��� ���� ��ȯ �޼ҵ�, �ϴܿ� ����.
bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

// �Է°��� wstring���� ����
bool Path::ExistFile(wstring path)
{
	/* 
		GetFileAttributes(LPCSTR LpFileName)
		�Ű������� c��Ÿ�� char*�̱� ������ c_str()�� ��ȯ�Ͽ� �Է�.
		��ο� �����ϴ� ������ �Ӽ��� ���Ͽ� Ȯ�� �� ��, ������ ��ȯ�� ��ȯ.

	*/
	DWORD fileValue = GetFileAttributes(path.c_str());
	
	// 0xFFFFFFFF���� ���� ��� : �������� ���� ����.
	// �� ���� ��� ������ �������� �ʴ´�.
	return fileValue < 0xFFFFFFFF;
}

// �Ű������� string���� �־��� ��� wstring���� �ٲ㼭 �ش� �޼ҵ� ����.
// �޼ҵ� �������̵�, �ش� �޼ҵ��� �� ������ �ϴ� wstring������ �ִ�.
bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWString(path));
}


// wstring���� �Է� ���� ��ο� ���丮�� �����ϴ��� Ȯ���ϴ� �޼ҵ�.
bool Path::ExistDirectory(wstring path)
{
	// ExistFile���� ����Ѵ�� GetFileAttributes�� �Ű������� C��Ÿ�� ���ڿ��� �䱸�ϱ� ������ c_str�� ��ȯ�Ͽ� �Է�
	DWORD attribute = GetFileAttributes(path.c_str());


	// INVALID_FILE_ATTRIBUTES : �ش� ���丮�� �������� �ʴ� ��� ��ȯ.
	// FILE_ATTRIBUTE_DIRECTORY : �ش� ������ �Ӽ��� ���丮�� ��� GetFileAttributes���� ��ȯ��.
	// �� temp�� attribute�� ���� INVALID_FILE_ATTIRVUTES�� �ƴϸ鼭 FILE_ATTRIVUTE_DIRECTORY�� ���� ��� true, �ƴ� ��� false�� ��ȯ �ϰ� �ȴ�.
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		(attribute & FILE_ATTRIBUTE_DIRECTORY));

	// temp�� true �̸� true/ false�̸� false ��ȯ.
	return temp == TRUE;
}


// string���� �־��� ��� 1, 2�� ���ļ� ��ȯ
string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

// combine�޼ҵ��� wstring ���� �޼ҵ� �����ε�
wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

// Combine �޼ҵ��� vector<string>���� �޼ҵ� �����ε�.
// vector������ ��� ���ҵ��� 0������ ���ļ� ��ȯ.
string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

// Combine �޼ҵ��� vector<wstring> ���� �޼ҵ� �����ε�.
wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

// path�� Directory �̸��� ��ȯ.
string Path::GetDirectoryName(string path)
{
	// ��ο� �����ϴ� '\\'�� ��Ȯ�� �ν��� ���Ͽ� "/"�� ��ȯ.
	String::Replace(&path, "\\", "/");
	// �ش� ���ڿ��� ������ '/'�� Ž�� �� ��, ���� ���� ������ (���� �ڿ� �ִ�) �ش� �ε��� ��ȯ
	size_t index = path.find_last_of('/');

	// �Է� ���ڿ��� ó������ / ����������(���� ���丮) ���ڿ� ��ȯ.
	return path.substr(0, index + 1);
}

// GetDirectoryName(string path) �޼ҵ��� wstring ���� �޼ҵ� �����ε�
wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

// �ش� ������ Ȯ���ڸ� ��� �޼ҵ�
string Path::GetExtension(string path)
{
	// "\\"�� '/'�� ��ȯ
	String::Replace(&path, "\\", "/");
	// ��ο� �����ϴ� ���� ���� ������ '.'�� ��ġ�� ��ȯ => �ش� ������ Ȯ���� ������ �����ϴ� '.', e.g. C:/test.cpp => test���� '.' ��ġ ��ȯ.
	size_t index = path.find_last_of('.');

	//'.'���ĺ��� ������ ���ڿ� ��ȯ : Ȯ����
	return path.substr(index + 1, path.length());;
}

// GetExtenstion()�� wstring ���� �޼ҵ� �������̵�.
wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

// �ش� ����� ���� �̸� ��ȯ �޼ҵ�, �Ű������� string.
string Path::GetFileName(string path)
{
	// Ÿ �޼ҵ忡�� �����ߵ��� ���� ����� "\\"�� '/'�� ��ȯ.
	String::Replace(&path, "\\", "/");
	// ����� �ڿ������� Ž���ؼ� ���� ���� ������ (���� �ڿ� �ִ�) '/'��ġ ��ȯ => �ش� ���丮.
	size_t index = path.find_last_of('/');

	// �ش� ��ο��� ���丮 ������ ��θ� ������ ���� �̸��� ��ȯ��.
	return path.substr(index + 1, path.length());
}

// �ش� ����� ���� �̸� ��ȯ �޼ҵ�, wstring���� �޼ҵ� �����ε�
wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

// ���� ��ο��� Ȯ���ڸ� ������ ������ ��� ��ȯ.
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);
	// ���� �̸����� '.'�� ��ġ�� ��ȯ, '.'�� �������� ���� �̸��� Ȯ���� ����.
	size_t index = fileName.find_last_of('.');

	// Ȯ���� ���������� ��θ� ��ȯ.
	return fileName.substr(0, index);
}

// GetFileNameWithoutExtension�� wstring���� �޼ҵ� �����ε�.
wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}


// ���� ������ ��ε�.
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model";
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";

// ��η� �־��� ������ �ҷ����� �޼ҵ�.
void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255]; // ������ �̸��� c_str()�� ��ȯ�Ͽ� ������ �迭
	wcscpy_s(name, file.c_str());

	// ������ �̸��� �޾ƿͼ� '\\'�� '/'�� ��ȯ�ϱ� ���� wstring
	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");


	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"�ҷ�����";
	ofn.nMaxFile = 255;
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			func(loadName);
		}
	}
}

// function<void(wstring)> : wstring�� �Ű������� ���� void Ÿ���� �Լ� ���ø�.
void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	/*
		OPENFILENAME : ���� ���� ���� ��ȭ������ �ʱⰪ�� ����.

typedef struct tagOFN {
  DWORD         lStructSize;
  HWND          hwndOwner;
  HINSTANCE     hInstance;
  LPCTSTR       lpstrFilter;
  LPTSTR        lpstrCustomFilter;
  DWORD         nMaxCustFilter;
  DWORD         nFilterIndex;
  LPTSTR        lpstrFile;
  DWORD         nMaxFile;
  LPTSTR        lpstrFileTitle;
  DWORD         nMaxFileTitle;
  LPCTSTR       lpstrInitialDir;
  LPCTSTR       lpstrTitle;
  DWORD         Flags;
  WORD          nFileOffset;
  WORD          nFileExtension;
  LPCTSTR       lpstrDefExt;
  LPARAM        lCustData;
  LPOFNHOOKPROC lpfnHook;
  LPCTSTR       lpTemplateName;
#if (_WIN32_WINNT >= 0x0500)
  void *        pvReserved;
  DWORD         dwReserved;
  DWORD         FlagsEx;
#endif // (_WIN32_WINNT >= 0x0500)
} OPENFILENAME, *LPOPENFILENAME; �� ���� ���·� ����.


	*/
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME); // �ش� ����ü�� ũ�� ����
	ofn.hwndOwner = hwnd; // �ش� ��ȭ������ ������ ����(�ڵ�), �ڵ� ���� ��� NULL
	ofn.lpstrFilter = filter; // ���� Ȯ���� ����.
	ofn.lpstrFile = name; // �ش� ���� �̸�.
	ofn.lpstrFileTitle = L"�����ϱ�";
	ofn.nMaxFile = 255;// lpstrFile�� �ִ� ����.
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR; // ����ڰ� �̿��� ���� ���丮�� �̵��ϴ���, ���� ���丮�� ������.

	// GetSaveFileName : saveFile�� �̸��� ��� �޼ҵ�, ������ true, �ƴϸ� false
	if (GetSaveFileName(&ofn) == TRUE)
	{
		// �Լ� ���ø��� ���������� �־����ٸ�
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			// �ش� �Լ��� loadName�� �Ű������� �־ ȣ��
			func(loadName);
		}
	}
}

// GetFiles�� �Ű������� string���� �־����� ��� wstring���� ��ȯ�Ͽ� �����ϴ� �޼ҵ� �����ε�.
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;// wstring���� ��ȯ�� ��ȯ �Ű������� �����ϱ� ���� ����
	wstring wPath = String::ToWString(path); // string���� �־��� path�� wstring���� ��ȯ
	wstring wFilter = String::ToWString(filter); // string���� �־��� filter�� wstring���� ��ȯ.

	// wstring���� ��ȯ�� �Ű������� �Է��ϰ� GetFiles �޼ҵ� ȣ��
	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	// GetFiles ȣ�� ���� ��ȯ�� ��ȯ �Ű��������� string���� ��ȯ�Ͽ� ���� �޼ҵ��� ��ȯ �Ű������� files ���Ϳ� string���� ��ȯ�Ͽ� push_back
	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

//path : ../Temp/
//filter : *.txt


// ����Լ��� �����Ǹ�, �ش� ��ο� �����ϴ� ��� ������ �̸����� files�� push_back�ϴ� �޼ҵ��̴�.(���丮�� �ƴ� ���ϵ鸸.)
void Path::GetFiles(vector<wstring>* files, wstring path, wstring filter, bool bFindSubFolder)
{
	wstring file = path + filter;

	/*
	typedef struct _WIN32_FIND_DATAA {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  CHAR     cFileName[MAX_PATH];
  CHAR     cAlternateFileName[14];
  DWORD    dwFileType;
  DWORD    dwCreatorType;
  WORD     wFinderFlags;
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
�� ���·� ����,  FindFirstFile, FindFirstFileEx, or FindNextFile���� �߰ߵ� file�� ������ ���� �ִ� ����ü�̴�.
	*/
	WIN32_FIND_DATA findData;

	// FindFirstFile = FindFirstFileW
	// �ش� �޼ҵ�� ���� �̸��� ã�� ���� �����͸� �Ű������� �޾Ƽ� �ش� ���丮�� ���� �Ǵ� ���� ���丮�� ã�� ��, handle�� ��ȯ�Ѵ�.
	HANDLE handle = FindFirstFile(file.c_str(), &findData);

	// ���� FindFirstFile�� ��ȯ���� INVALID_HANDLE_VALUE�̸� (�ش� ���丮�� ����/���丮�� �������� �ʴ´ٸ�)
	// �޼ҵ� ����.
	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{		// Ž���� ������ ���丮�̸� ���� �ڵ� ����, �ƴ� ��� else�� �̵�.
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				// bFindSubFolder : �ش� �޼ҵ��� �Ű������̰�, ���� ���丮�� ã������ true�� �־���.
				// findData.cFileName[0] : findData�� FindFirstFile�޼ҵ忡�� Ž���� ������ �Ӽ��̴�. cFileName[]�� �ش� ������ �̸��� ������ �迭�̴�.
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";

				// �ش� ���� '.'�̸� ���� ��ο� �ش� ���� �̸��� �߰��� ��, GetFiles �޼ҵ� ȣ���Ѵ�(����Լ�.)
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else
			{
				// �ش� ������ ���丮�� �ƴ϶��(�����̶��) fileName�� �ش� ������ ��θ� ���� �� ��, files ���Ϳ� push_back �Ѵ�.
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
			// 
		} while (FindNextFile(handle, &findData));// ���̻� ����/���丮�� ���� �� ���� �ݺ�.

		FindClose(handle);
	}
}

// �־��� ��ο� ���� �����ϴ� �޼ҵ�, string���� �Ű����� �־��� ����� �޼ҵ� �����ε�
void Path::CreateFolder(string path)
{
	// wstring���� ��ȯ�ؼ� �޼ҵ� ȣ��
	CreateFolder(String::ToWString(path));
}

// path�� wstring���� �޾Ƽ� �ش� ���丮�� �� ���丮�� �����ϴ� �޼ҵ�
void Path::CreateFolder(wstring path)
{
	// ������ �̸��� ���丮�� �����ϸ� �ȵǱ� ������ �̹� �����ϴ� ��� �޼ҵ� ����
	if (ExistDirectory(path) == false)
		// �ش� �޼ҵ��� �Ű������� c��Ÿ�� ���ڿ��̱� ������ c_str�� �����Ͽ� �Է�
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

// �������� ���丮�� �����ϴ� �޼ҵ�
// ���丮 ���ο� ���丮�� ���������� �����Ѵ�.
void Path::CreateFolders(wstring path)
{
	// �־��� ����� '\\'�� '/'�� ��ȯ�Ѵ�/ 
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;// �� ��� ���� �����ϴ� ���丮�� �̸��� �����ϱ� ���� ����
	String::SplitString(&folders, path, L"/"); // �־��� ��ο� ��� ���丮���� �̸��� ���ϱ� ���� �޼ҵ�.

	// �� ���丮 ��� �ۼ��� ���� �ʱ�ȭ
	wstring temp = L"";

	// folders ���Ϳ� ����� ������ ���丮 �̸��� ó������ ����.
	// folders�� ��� e.g. C:/A/B/C/D�� ��η� �־��� �� {C:, A, B, C, D}�� ���·� ����Ǿ� ���� ���̴�.
	// 0�� �ε������� �ش� ���丮�� �����ϸ� �Ѿ��, �������� �ʴ°�� ���丮�� ������ ���� ���̴�.
	// �ѹ� ���丮�� �����Ǹ� �� ���ĺ��ʹ� ��� ���丮�� ������ ���� ���̴�.
	for (wstring folder : folders)
	{
		// temp �� �ش� ������ ������ ���丮�� �̸��̴�.
		temp += folder + L"/";
		// temp��� ���丮 ����.
		CreateFolder(temp);
	}
}
