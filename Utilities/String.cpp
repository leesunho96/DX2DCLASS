#include "stdafx.h"
#include "String.h"

//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ� �ڸ���
///@param orgin : ���� ���ڿ�
///@param tok : �ڸ� ������ �Ǵ� ���ڿ�
///@return �Ϸ�� ���ڿ� �迭
//////////////////////////////////////////////////////////////////////////
void String::SplitString(vector<string>* result, string origin, string tok)
{
	// ��� �Ű����� result�� �ʱ�ȭ. => ������ ���� �� �𸣴� ���͸� �ʱ�ȭ�Ѵ�. ��Ȯ�� ��ȯ���� ����
	result->clear();

	// �Է� string �ڸ� ��ġ
	int cutAt = 0; //�ڸ� ��ġs

	// string.npos : ã�� ���ڿ��� ���� ��� ��ȯ��.
	// string.find_first_of(tok) : �Ű����� tok�� ������ character�� ���ؼ� string���� ���� ���� ������ character �� index ��ȯ.
	// e.g. string : "abcd", tok : "cde" : return���� 2.
	// ���� ��ġ�� ��찡 ���� ��� (e.g. string : "ABCD", tok :: "QWER") string.npos�� ��ȯ��.

	// �� �ش� �ڵ�� origin�� ���ؼ� tok�� �ش��ϴ� ��Ұ� ���� ������ �ش� ���ڿ��� �ɰ�.
	// ���� ����.
	// string : "ABCDABCD", tok : "CD"
	// => result ���� ABC D ABC D�� �Է� �� ��.
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}


	// �ش� �ڵ� ����Ǵ� ����
	// string : "ABCDABCDEEE", tok : "D"
	// => result ���Ϳ��� "ABCD" "ABCD"�� push�Ǿ� �ְ� string���� EEE�� �������� ��.
	// �ش� EEE�� result�� push : ������ �ȵǴϱ�.
	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}

// ���� SplitString�� wstring ���� �޼ҵ� �����ε�
void String::SplitString(vector<wstring>* result, wstring origin, wstring tok)
{
	result->clear();

	int cutAt = 0; //�ڸ� ��ġs
	while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
	{
		if (cutAt > 0) //�ڸ��� ��ġ�� 0����ũ��
			result->push_back(origin.substr(0, cutAt));

		origin = origin.substr(cutAt + 1);
	}

	if (origin.length() > 0) //�ڸ��� ���� ���� �ִٸ�
		result->push_back(origin.substr(0, cutAt));
}


//////////////////////////////////////////////////////////////////////////
///@brief ���� ���ڿ��� ������ üũ
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : ���� �񱳹��ڿ�
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
///@brief �ش� ���ڿ��� ���ԵǾ� �ִ���
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
//////////////////////////////////////////////////////////////////////////

// str�� comp�� ���ԵǾ� ������ true �ƴϸ� false ��ȯ
bool String::Contain(string str, string comp)
{
	//found�� str���� comp�� ���� �ɰ��̴�.
	// ���� str�� comp�� ��ġ�� ������ ���ٸ� wstring:npos�� �� ��
	size_t found = str.find(comp);

	return found != wstring::npos;
}

//Contain�� wstring���� �޼ҵ� �����ε�
bool String::Contain(wstring str, wstring comp)
{
	size_t found = str.find(comp);

	return found != wstring::npos;
}


//////////////////////////////////////////////////////////////////////////
///@brief �ش� ���ڿ����� comp ���ڸ� rep�� ����
///@param str : üũ�Ϸ��� ���ڿ�
///@param comp : �񱳹��ڿ�
///@param rep : �ٲܹ��ڿ�
//////////////////////////////////////////////////////////////////////////

// ���� str���� comp�� ã�� rep�� ��ȯ�ϴ� �޼ҵ�.
void String::Replace(string * str, string comp, string rep)
{
	// �ӽ� ���� temp�� str�� �ʱ�ȭ.
	string temp = *str;
	// string�� ���Ͽ� ���縦 ���� index ����
	size_t start_pos = 0;

	// start_pos�� wstring::npos�� �� ������ => temp�� comp�� ��ġ�� ���̽��� ���� �� ���� ����.
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		// temp�� start_pos���� ���� ���ڿ� ���̸�ŭ�� rep�� �����Ѵ�.
		// e.g. temp = "ABCD", comp = "D", rep = "QWER"
		// start_pos�� 3�� �� ���̰�, comp.length() = 1�� �� ���̴�.
		// temp�� index 3�� 4���̿� rep�� ����. => "ABCQWER"�� �� ��.
		temp.replace(start_pos, comp.length(), rep);
		// ���ڿ��� ���� �Ͽ��� ������ ���ڿ� ���� ���� ������ ���� ���ڿ� ���ķ� ��������� �Ѵ�.
		start_pos += rep.length();
	}

	// ���� �Ϸ�� ���ڿ��� ��ȯ.
	*str = temp;
}

// �� Replace �޼ҵ��� wstring Ÿ�� �޼ҵ� �����ε�.
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
///@brief string���� wstring������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
wstring String::ToWString(string value)
{
	// string value�� wstring���� ��ȯ
	wstring temp = L"";
	temp.assign(value.begin(), value.end());

	return temp;
}

//////////////////////////////////////////////////////////////////////////
///@brief wstring���� string������ ����
///@param value : ��ȯ�� ���ڿ�
///@return ��ȯ �Ϸ� ���ڿ�
//////////////////////////////////////////////////////////////////////////
string String::ToString(wstring value)
{
	// wstring value�� string���� ��ȯ
	string temp = "";
	temp.assign(value.begin(), value.end());

	return temp;
}
//////////////////////////////////////////////////////////////////////////