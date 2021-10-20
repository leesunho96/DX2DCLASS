#include "stdafx.h"
#include "String.h"

//////////////////////////////////////////////////////////////////////////
///@brief 문자열 자르기
///@param orgin : 원본 문자열
///@param tok : 자를 기준이 되는 문자열
///@return 완료된 문자열 배열
//////////////////////////////////////////////////////////////////////////
void String::SplitString(vector<string>* result, string origin, string tok)
{
	// 출력 매개변수 result를 초기화. => 기존에 있을 지 모르는 벡터를 초기화한다. 정확한 반환값을 위함
	result->clear();

	// 입력 string 자를 위치
	int cutAt = 0; //자를 위치s

	// string.npos : 찾는 문자열이 없는 경우 반환됨.
	// string.find_first_of(tok) : 매개변수 tok의 각각의 character에 대해서 string에서 가장 먼저 나오는 character 의 index 반환.
	// e.g. string : "abcd", tok : "cde" : return값은 2.
	// 만약 겹치는 경우가 없는 경우 (e.g. string : "ABCD", tok :: "QWER") string.npos가 반환됨.

	// 즉 해당 코드는 origin에 대해서 tok에 해당하는 요소가 없을 때까지 해당 문자열을 쪼갬.
	// 실행 예시.
	// string : "ABCDABCD", tok : "CD"
	// => result 에는 ABC D ABC D로 입력 될 것.
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다크면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}


	// 해당 코드 수행되는 예시
	// string : "ABCDABCDEEE", tok : "D"
	// => result 벡터에는 "ABCD" "ABCD"가 push되어 있고 string에는 EEE가 남아있을 것.
	// 해당 EEE를 result에 push : 버리면 안되니까.
	if (origin.length() > 0) //자르고도 남은 것이 있다면
		result->push_back(origin.substr(0, cutAt));
}

// 위의 SplitString의 wstring 버전 메소드 오버로딩
void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //자를 위치s
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //자르는 위치가 0보다크면
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //자르고도 남은 것이 있다면
		result->push_back(origin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief 시작 문자열이 같은지 체크
///@param str : 체크하려는 문자열
///@param comp : 시작 비교문자열
//////////////////////////////////////////////////////////////////////////
bool String::StartsWith(string str, string comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

bool String::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && (int)index == 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열이 포함되어 있는지
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
//////////////////////////////////////////////////////////////////////////

// str에 comp가 포함되어 있으면 true 아니면 false 반환
bool String::Contain(string str, string comp)
{
	//found는 str에서 comp의 수가 될것이다.
	// 만약 str과 comp가 겹치는 내용이 없다면 wstring:npos가 될 것
	size_t found = str.find(comp);

	return found != wstring::npos;
}

//Contain의 wstring버전 메소드 오버로딩
bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief 해당 문자열에서 comp 문자를 rep로 변경
///@param str : 체크하려는 문자열
///@param comp : 비교문자열
///@param rep : 바꿀문자열
//////////////////////////////////////////////////////////////////////////

// 원본 str에서 comp를 찾아 rep로 변환하는 메소드.
void String::Replace(string * str, string comp, string rep)
{
	// 임시 변수 temp를 str로 초기화.
	string temp = *str;
	// string에 대하여 조사를 위한 index 변수
	size_t start_pos = 0;

	// start_pos가 wstring::npos가 될 때까지 => temp에 comp가 겹치는 케이스가 없을 떄 까지 수행.
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		// temp를 start_pos부터 기존 문자열 길이만큼을 rep로 변경한다.
		// e.g. temp = "ABCD", comp = "D", rep = "QWER"
		// start_pos는 3이 될 것이고, comp.length() = 1이 될 것이다.
		// temp의 index 3과 4사이에 rep를 삽입. => "ABCQWER"가 될 것.
		temp.replace(start_pos, comp.length(), rep);
		// 문자열을 삽입 하였기 때문에 문자열 조사 시작 지점을 삽입 문자열 이후로 변경해줘야 한다.
		start_pos += rep.length();
	}

	// 변경 완료된 문자열을 반환.
	*str = temp;
}

// 위 Replace 메소드의 wstring 타입 메소드 오버로딩.
void String::Replace(wstring* str, wstring comp, wstring rep)
{
	wstring temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	*str = temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief string형을 wstring형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
wstring String::ToWString(string value)
{
	// string value를 wstring으로 변환
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring형을 string형으로 변경
///@param value : 변환할 문자열
///@return 변환 완료 문자열
//////////////////////////////////////////////////////////////////////////
string String::ToString(wstring value)
{
	// wstring value를 string으로 변환
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
//////////////////////////////////////////////////////////////////////////