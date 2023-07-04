//-----------------------------------------------------------------------------
// File: GetI
//
// Desc: Singleton Ŭ����
//
//		[Variables]
//		- instance: �ش� �ν��Ͻ�
//
//		[Functions]
//		- GetInstance: �ش� �ν��Ͻ� ���� (���� ��� ����)
//-----------------------------------------------------------------------------

#pragma once

template <class T> class GetI
{
protected:
	static T* instance;

public:
	virtual ~GetI() { delete instance; }

	static T* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new T();
		}

		return instance;
	};
};

template<class T> T* GetI<T>::instance = 0;