#pragma once
#include "Global.h"
#include <mutex>

class CMutex
{
public:
	CMutex() = default;
	virtual ~CMutex() = default;

public:
	void lock() const
	{
		return this->m_oMutex.lock();
	}

	void unlock() const
	{
#pragma warning( push )
#pragma warning( disable : 26110)
		return this->m_oMutex.unlock();
#pragma warning( pop ) 
	}

	bool tryLock() const
	{
		return this->m_oMutex.try_lock();
	}

private:
	mutable std::recursive_mutex m_oMutex;
};
