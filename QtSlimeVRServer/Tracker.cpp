#include "Tracker.h"

CTracker::CTracker(): m_bIsReady(false)
{
}

std::shared_ptr<VRTracker::CIMUTracker> CTracker::imuTrackerById(uint32_t i_nId)
{
	std::shared_ptr<VRTracker::CIMUTracker> pTracker = nullptr;
	switch (i_nId)
	{
	case 0: pTracker = m_pTracker0; break;
	case 1: pTracker = m_pTracker1; break;
	}
	return pTracker;
}

void CTracker::setImuTracker(uint32_t i_nId, std::shared_ptr<VRTracker::CIMUTracker> i_pTracker)
{
	switch (i_nId)
	{
	case 0:  
		this->m_pTracker0 = i_pTracker;
		break;
	case 1: 
		this->m_pTracker1 = i_pTracker;
		break;
	}
}
