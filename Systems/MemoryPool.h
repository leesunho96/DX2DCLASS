#pragma once
#include <stack>




template<typename T>
class CObjectPool
{
public:
	// �����ŭ ������Ʈ�� �����.
	CObjectPool(int size = 100) {
		_maxSize = size;

		for (int i = 0; i < _maxSize; ++i) {
			T* newObject = new T();
			_objects.push(newObject);
		}
	}

	// ������Ʈ�� ����.
	~CObjectPool()
	{
	
		while (!_objects.empty()) {
			T* object = _objects.top();
			_objects.pop();
			delete object;
		}

		_maxSize = 0;
	}

	// ������Ʈ�� ������.
	T* PopObject()
	{
	

		// ������Ʈ�� ���ٸ� Ȯ���Ѵ�.
		if (_objects.empty()) {
			Expand();
		}

		T* retVal = _objects.top();
		_objects.pop();
		return retVal;
	}

	// ���� ũ�⸸ŭ ���ο� ������Ʈ�� �־� Ȯ���Ѵ�.
	void Expand() {
		// �ø� ũ�⸸ŭ ���ο� ������Ʈ�� �־��ش�.
		for (int i = 0; i < _maxSize; ++i)
		{
			T* newObject = new T();
			_objects.push(newObject);
		}

		// �ִ� ũ�⸦ �ø���.
		_maxSize += _maxSize;
	}

	// ������Ʈ�� �����Ѵ�.
	void ReturnObject(T* object)
	{		_objects.push(object);
	}

private:
	
	std::stack<T*> _objects;
	int _maxSize; // �ִ� �迭 ũ��
};