#pragma once
#include "stdafx.h"
#include <stack>

template<typename T>
class MemoryPool
{
public:
	// 사이즈만큼 오브젝트를 만든다.
	MemoryPool() {}

	// 오브젝트를 비운다.
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

	// 오브젝트를 꺼낸다.
	T* PopObject()
	{
		// 오브젝트가 없다면 확장한다.
		if (_objects.empty()) {
			return nullptr;
		}
		T* retVal = _objects.at(_objects.end());
		_objects.pop_back();
		activateObjects.push_back(retVal);
		return retVal;
	}

	// 오브젝트를 수거한다.
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


