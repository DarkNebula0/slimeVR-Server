#include "Tracker.h"

std::atomic<uint32_t> VRTracker::CTracker::s_nTrackerId{ 0 };

VRTracker::CTracker::CTracker(uint32_t i_nId, const std::string_view i_stName)
	: m_stName(i_stName), m_eStatus(ETrackerStatus::Disconnected), m_rConfidenceLevel(0.0f)
	, m_pTrackerPos(&s_aoTrackerPosition[ETrackerPosition::None]), m_nId(i_nId)
{
}


VRTracker::CTracker::CTracker()
: m_stName(""), m_eStatus(ETrackerStatus::Disconnected), m_rConfidenceLevel(0.0f)
, m_pTrackerPos(&s_aoTrackerPosition[ETrackerPosition::None]), m_nId(0) 
{
};