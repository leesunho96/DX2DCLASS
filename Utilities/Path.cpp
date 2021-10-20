#include "stdafx.h"
#include "Path.h"
#include <string.h>
#include "String.h"

// string 으로 주어진 path를 wstring으로 바꿔서 수행.
// ExistFile는 해당 경로에 파일이 존재하는지 여부 반환 메소드, 하단에 정의.
bool Path::ExistFile(string path)
{
	return ExistFile(String::ToWString(path));
}

// 입력값을 wstring으로 받음
bool Path::ExistFile(wstring path)
{
	/* 
		GetFileAttributes(LPCSTR LpFileName)
		매개변수가 c스타일 char*이기 때문에 c_str()로 변환하여 입력.
		경로에 존재하는 파일의 속성에 대하여 확인 한 후, 적절한 반환값 반환.

	*/
	DWORD fileValue = GetFileAttributes(path.c_str());
	
	// 0xFFFFFFFF보다 작은 경우 : 정상적인 파일 존재.
	// 그 외의 경우 파일은 존재하지 않는다.
	return fileValue < 0xFFFFFFFF;
}

// 매개변수가 string으로 주어진 경우 wstring으로 바꿔서 해당 메소드 실행.
// 메소드 오버라이딩, 해당 메소드의 상세 구현은 하단 wstring버전에 있다.
bool Path::ExistDirectory(string path)
{
	return ExistDirectory(String::ToWString(path));
}


// wstring으로 입력 받은 경로에 디렉토리가 존재하는지 확인하는 메소드.
bool Path::ExistDirectory(wstring path)
{
	// ExistFile에서 명시한대로 GetFileAttributes는 매개변수로 C스타일 문자열을 요구하기 때문에 c_str로 변환하여 입력
	DWORD attribute = GetFileAttributes(path.c_str());


	// INVALID_FILE_ATTRIBUTES : 해당 디렉토리가 존재하지 않는 경우 반환.
	// FILE_ATTRIBUTE_DIRECTORY : 해당 파일의 속성이 디렉토리인 경우 GetFileAttributes에서 반환됨.
	// 즉 temp는 attribute의 값이 INVALID_FILE_ATTIRVUTES가 아니면서 FILE_ATTRIVUTE_DIRECTORY와 같은 경우 true, 아닌 경우 false를 반환 하게 된다.
	BOOL temp = (attribute != INVALID_FILE_ATTRIBUTES &&
		(attribute & FILE_ATTRIBUTE_DIRECTORY));

	// temp가 true 이면 true/ false이면 false 반환.
	return temp == TRUE;
}


// string으로 주어진 경로 1, 2를 합쳐서 반환
string Path::Combine(string path1, string path2)
{
	return path1 + path2;
}

// combine메소드의 wstring 버전 메소드 오버로딩
wstring Path::Combine(wstring path1, wstring path2)
{
	return path1 + path2;
}

// Combine 메소드의 vector<string>버전 메소드 오버로딩.
// vector내부의 모든 원소들을 0번부터 합쳐서 반환.
string Path::Combine(vector<string> paths)
{
	string temp = "";
	for (string path : paths)
		temp += path;

	return temp;
}

// Combine 메소드의 vector<wstring> 버전 메소드 오버로딩.
wstring Path::Combine(vector<wstring> paths)
{
	wstring temp = L"";
	for (wstring path : paths)
		temp += path;

	return temp;
}

// path의 Directory 이름을 반환.
string Path::GetDirectoryName(string path)
{
	// 경로에 존재하는 '\\'를 정확한 인식을 위하여 "/"로 변환.
	String::Replace(&path, "\\", "/");
	// 해당 문자열의 끝부터 '/'를 탐색 한 후, 가장 먼저 나오는 (가장 뒤에 있는) 해당 인덱스 반환
	size_t index = path.find_last_of('/');

	// 입력 문자열의 처음부터 / 이전까지의(현재 디렉토리) 문자열 반환.
	return path.substr(0, index + 1);
}

// GetDirectoryName(string path) 메소드의 wstring 버전 메소드 오버로딩
wstring Path::GetDirectoryName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(0, index + 1);
}

// 해당 파일의 확장자를 얻는 메소드
string Path::GetExtension(string path)
{
	// "\\"를 '/'로 변환
	String::Replace(&path, "\\", "/");
	// 경로에 존재하는 가장 먼저 나오는 '.'의 위치를 반환 => 해당 파일의 확장자 이전에 존재하는 '.', e.g. C:/test.cpp => test뒤의 '.' 위치 반환.
	size_t index = path.find_last_of('.');

	//'.'이후부터 끝까지 문자열 반환 : 확장자
	return path.substr(index + 1, path.length());;
}

// GetExtenstion()의 wstring 버전 메소드 오버라이딩.
wstring Path::GetExtension(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('.');

	return path.substr(index + 1, path.length());;
}

// 해당 경로의 파일 이름 반환 메소드, 매개변수는 string.
string Path::GetFileName(string path)
{
	// 타 메소드에서 설명했듯이 파일 경로의 "\\"를 '/'로 변환.
	String::Replace(&path, "\\", "/");
	// 경로의 뒤에서부터 탐색해서 가장 먼저 나오는 (가장 뒤에 있는) '/'위치 반환 => 해당 디렉토리.
	size_t index = path.find_last_of('/');

	// 해당 경로에서 디렉토리 까지의 경로를 제거한 파일 이름만 반환됨.
	return path.substr(index + 1, path.length());
}

// 해당 경로의 파일 이름 반환 메소드, wstring버전 메소드 오버로딩
wstring Path::GetFileName(wstring path)
{
	String::Replace(&path, L"\\", L"/");
	size_t index = path.find_last_of('/');

	return path.substr(index + 1, path.length());
}

// 파일 경로에서 확장자를 제거한 형태의 경로 반환.
string Path::GetFileNameWithoutExtension(string path)
{
	string fileName = GetFileName(path);
	// 파일 이름에서 '.'의 위치를 반환, '.'을 기준으로 파일 이름과 확장자 구분.
	size_t index = fileName.find_last_of('.');

	// 확장자 이전까지의 경로를 반환.
	return fileName.substr(0, index);
}

// GetFileNameWithoutExtension의 wstring버전 메소드 오버로딩.
wstring Path::GetFileNameWithoutExtension(wstring path)
{
	wstring fileName = GetFileName(path);

	size_t index = fileName.find_last_of('.');
	return fileName.substr(0, index);
}


// 각각 파일의 경로들.
const WCHAR* Path::ImageFilter = L"Image\0*.png;*.bmp;*.jpg";
const WCHAR* Path::BinModelFilter = L"Binary Model\0*.model";
const WCHAR* Path::FbxModelFilter = L"Fbx Model\0*.fbx;*.obj\0";
const WCHAR* Path::ShaderFilter = L"HLSL file\0*.hlsl";

// 경로로 주어진 파일을 불러오는 메소드.
void Path::OpenFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255]; // 파일의 이름을 c_str()로 변환하여 저장할 배열
	wcscpy_s(name, file.c_str());

	// 폴더의 이름을 받아와서 '\\'를 '/'로 변환하기 위한 wstring
	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");


	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = name;
	ofn.lpstrFileTitle = L"불러오기";
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

// function<void(wstring)> : wstring을 매개변수로 갖는 void 타입의 함수 템플릿.
void Path::SaveFileDialog(wstring file, const WCHAR* filter, wstring folder, function<void(wstring)> func, HWND hwnd)
{
	WCHAR name[255];
	wcscpy_s(name, file.c_str());

	wstring tempFolder = folder;
	String::Replace(&tempFolder, L"/", L"\\");

	/*
		OPENFILENAME : 파일 열기 공통 대화상자의 초기값을 지정.

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
} OPENFILENAME, *LPOPENFILENAME; 과 같은 형태로 선언.


	*/
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME); // 해당 구조체의 크기 지정
	ofn.hwndOwner = hwnd; // 해당 대화상자의 소유자 지정(핸들), 핸들 없는 경우 NULL
	ofn.lpstrFilter = filter; // 파일 확장자 필터.
	ofn.lpstrFile = name; // 해당 파일 이름.
	ofn.lpstrFileTitle = L"저장하기";
	ofn.nMaxFile = 255;// lpstrFile의 최대 길이.
	ofn.lpstrInitialDir = tempFolder.c_str();
	ofn.Flags = OFN_NOCHANGEDIR; // 사용자가 이용을 위해 디렉토리를 이동하더라도, 현재 디렉토리는 유지됨.

	// GetSaveFileName : saveFile의 이름을 얻는 메소드, 성공시 true, 아니면 false
	if (GetSaveFileName(&ofn) == TRUE)
	{
		// 함수 템플릿이 정상적으로 주어졌다면
		if (func != NULL)
		{
			wstring loadName = name;
			String::Replace(&loadName, L"\\", L"/");

			// 해당 함수를 loadName를 매개변수로 주어서 호출
			func(loadName);
		}
	}
}

// GetFiles의 매개변수가 string으로 주어졌을 경우 wstring으로 변환하여 수행하는 메소드 오버로딩.
void Path::GetFiles(vector<string>* files, string path, string filter, bool bFindSubFolder)
{
	vector<wstring> wFiles;// wstring에서 반환될 반환 매개변수를 저장하기 위한 벡터
	wstring wPath = String::ToWString(path); // string으로 주어진 path를 wstring으로 변환
	wstring wFilter = String::ToWString(filter); // string으로 주어진 filter를 wstring으로 변환.

	// wstring으로 변환한 매개변수를 입력하고 GetFiles 메소드 호출
	GetFiles(&wFiles, wPath, wFilter, bFindSubFolder);

	// GetFiles 호출 이후 반환된 반환 매개변수들을 string으로 변환하여 현재 메소드의 반환 매개변수인 files 벡터에 string으로 변환하여 push_back
	for (wstring str : wFiles)
		files->push_back(String::ToString(str));
}

//path : ../Temp/
//filter : *.txt


// 재귀함수로 구현되며, 해당 경로에 존재하는 모든 파일의 이름들을 files에 push_back하는 메소드이다.(디렉토리가 아닌 파일들만.)
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
위 형태로 정의,  FindFirstFile, FindFirstFileEx, or FindNextFile에서 발견된 file의 정보를 갖고 있는 구조체이다.
	*/
	WIN32_FIND_DATA findData;

	// FindFirstFile = FindFirstFileW
	// 해당 메소드는 파일 이름과 찾을 파일 데이터를 매개변수로 받아서 해당 디렉토리에 파일 또는 하위 디렉토리를 찾은 후, handle를 반환한다.
	HANDLE handle = FindFirstFile(file.c_str(), &findData);

	// 만약 FindFirstFile의 반환값이 INVALID_HANDLE_VALUE이면 (해당 디렉토리에 파일/디렉토리가 존재하지 않는다면)
	// 메소드 종료.
	if (handle != INVALID_HANDLE_VALUE)
	{
		do
		{		// 탐색한 파일이 디렉토리이면 다음 코드 수행, 아닌 경우 else로 이동.
			if (findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				// bFindSubFolder : 해당 메소드의 매개변수이고, 하위 디렉토리를 찾았으면 true로 주어짐.
				// findData.cFileName[0] : findData는 FindFirstFile메소드에서 탐색한 파일의 속성이다. cFileName[]는 해당 파일의 이름을 저장한 배열이다.
				if (bFindSubFolder == true && findData.cFileName[0] != '.')
				{
					wstring folder = path + wstring(findData.cFileName) + L"/";

				// 해당 값이 '.'이면 폴더 경로에 해당 파일 이름을 추가한 후, GetFiles 메소드 호출한다(재귀함수.)
					GetFiles(files, folder, filter, bFindSubFolder);
				}
			}
			else
			{
				// 해당 파일이 디렉토리가 아니라면(파일이라면) fileName에 해당 파일의 경로를 저장 한 후, files 벡터에 push_back 한다.
				wstring fileName = path + wstring(findData.cFileName);
				files->push_back(fileName);
			}
			// 
		} while (FindNextFile(handle, &findData));// 더이상 파일/디렉토리가 없을 떄 까지 반복.

		FindClose(handle);
	}
}

// 주어진 경로에 폴더 생성하는 메소드, string으로 매개변수 주어진 경우의 메소드 오버로딩
void Path::CreateFolder(string path)
{
	// wstring으로 변환해서 메소드 호출
	CreateFolder(String::ToWString(path));
}

// path를 wstring으로 받아서 해당 디렉토리에 새 디렉토리를 생성하는 메소드
void Path::CreateFolder(wstring path)
{
	// 동일한 이름의 디렉토리가 존재하면 안되기 때문에 이미 존재하는 경우 메소드 종료
	if (ExistDirectory(path) == false)
		// 해당 메소드의 매개변수는 c스타일 문자열이기 때문에 c_str로 변경하여 입력
		CreateDirectory(path.c_str(), NULL);
}

void Path::CreateFolders(string path)
{
	CreateFolders(String::ToWString(path));
}

// 여러개의 디렉토리를 생성하는 메소드
// 디렉토리 내부에 디렉토리를 연쇄적으로 생성한다.
void Path::CreateFolders(wstring path)
{
	// 주어진 경로의 '\\'를 '/'로 변환한다/ 
	String::Replace(&path, L"\\", L"/");

	vector<wstring> folders;// 각 경로 내에 존재하는 디렉토리의 이름을 저장하기 위한 벡터
	String::SplitString(&folders, path, L"/"); // 주어진 경로에 모든 디렉토리들의 이름을 구하기 위한 메소드.

	// 각 디렉토리 경로 작성을 위한 초기화
	wstring temp = L"";

	// folders 벡터에 저장된 각각의 디렉토리 이름을 처음부터 생성.
	// folders의 경우 e.g. C:/A/B/C/D를 경로로 주었을 떄 {C:, A, B, C, D}의 형태로 저장되어 있을 것이다.
	// 0번 인덱스부터 해당 디렉토리가 존재하면 넘어가고, 존재하지 않는경우 디렉토리를 생성해 나갈 것이다.
	// 한번 디렉토리가 생성되면 그 이후부터는 계속 디렉토리를 생성해 나갈 것이다.
	for (wstring folder : folders)
	{
		// temp 는 해당 순서에 생성될 디렉토리의 이름이다.
		temp += folder + L"/";
		// temp라는 디렉토리 생성.
		CreateFolder(temp);
	}
}
