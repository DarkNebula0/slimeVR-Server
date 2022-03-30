#include "ComputedTracker.h"

VRTracker::CComputedTracker::CComputedTracker(uint32_t i_nId, const std::string_view i_stSerial, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition)
	: CTracker(i_nId, i_stName), m_stSerial(i_stSerial), m_bHasRotation(i_bHasRotation), m_bHasPosition(i_bHasPosition)
{
	this->setConfidenceLevel(-1);
}

VRTracker::CComputedTracker::CComputedTracker(uint32_t i_nId, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition)
	: CComputedTracker(i_nId, i_stName, i_stName, i_bHasRotation, i_bHasPosition)
{}

bool VRTracker::CComputedTracker::position(QVector3D &i_oStore)
{
	i_oStore = this->m_oPosition;
	return true;
}

bool VRTracker::CComputedTracker::rotation(QQuaternion& i_oStore)
{
	i_oStore = this->m_oRotation;
	return false;
}
