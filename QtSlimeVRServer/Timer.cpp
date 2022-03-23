#include "Timer.h"


void CTimer::start()
{
	this->m_fIsStarted = true;
	this->m_oStartTime = std::chrono::high_resolution_clock::now();
}

uint64_t CTimer::elapsed() const
{
	return (this->isStarted()
		? std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - this->m_oStartTime).count()
		: 0);
}
