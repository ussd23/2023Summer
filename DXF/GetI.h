//-----------------------------------------------------------------------------
// File: GetI
//
// Desc: Singleton 클래스
//
//		[Variables]
//		- instance: 해당 인스턴스
//
//		[Functions]
//		- GetInstance: 해당 인스턴스 리턴 (없을 경우 생성)
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