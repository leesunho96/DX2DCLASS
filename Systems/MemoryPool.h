#pragma once
#include "stdafx.h"
#include <stack>

template<typename T>
class MemoryPool
{
public:
	// �����ŭ ������Ʈ�� �����.
	MemoryPool() {}

	// ������Ʈ�� ����.
	~MemoryPool()
	{	
		while (!_objects.empty()) {
			T* object = _objects.top();
			_objects.pop();
			SAFE_DELETE(object);
		}		
	}

	void PushObject(T* input)
	{	
		_objects.push(input);
	}

	void CheckObjectPool() 
	{
		for (int i = 0; i < activateObjects.size();)
		{
			if (objects->GetIsValid())
			{
				activateObjects.erase(activateObjects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	};

	// ������Ʈ�� ������.
	T* PopObject()
	{
		// ������Ʈ�� ���ٸ� Ȯ���Ѵ�.
		if (_objects.empty()) {
			return nullptr;
		}
		T* retVal = _objects.at(_objects.end());
		_objects.pop_back();
		activateObjects.push_back(retVal);
		return retVal;
	}

	// ������Ʈ�� �����Ѵ�.
	void ReturnObject(T* object)
	{		
		_objects.push(object);
	}

	void Update(D3DXMATRIX& V, D3DXMATRIX& P)
	{
		for (auto objects : activateObjects)
		{
			objects->Update(V, P);
		}
	}

	void Render()
	{
		for (auto objects : activateObjects)
		{
			objects->Render();
		}
	}

private:	
	vector<T*> _objects;
	vector<T*> activateObjects;
};


