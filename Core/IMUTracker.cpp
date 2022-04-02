#include "IMUTracker.h"

float VRTracker::CIMUTracker::s_rMaxMagCorrectionAccuracy = 5 * (180.0f / M_PI);

VRTracker::CIMUTracker::CIMUTracker(std::string_view i_stName)
	: CTracker(CTracker::getNextId(), i_stName)
{
}

void VRTracker::CIMUTracker::calculateLiveMagnetometerCorrection()
{}

bool VRTracker::CIMUTracker::position(QVector3D& i_oStore)
{
	i_oStore.setX(0.0f);
	i_oStore.setY(0.0f);
	i_oStore.setZ(0.0f);
	return false;
}

bool VRTracker::CIMUTracker::rotation(QQuaternion& i_oStore)
{
	i_oStore = this->m_oRotQuaternion * this->m_oRotAdjust;
	return true;
}

void VRTracker::CIMUTracker::resetYaw(const QQuaternion& i_oReference)
{
	if (this->m_nMagCalibrationStatus >= static_cast<uint32_t>(ECalibrationAccuracy::High)) {
		this->m_bIsMagentometerCalibrated = true;
		this->m_oCorrection = this->m_oRotQuaternion.inverted() * this->m_oRotMagQuaternion;
	}
}

void VRTracker::CIMUTracker::tick()
{
	if (this->m_bIsMagentometerCalibrated && this->m_bHasNewCorrectionData) {
		this->m_bHasNewCorrectionData = false;
		if (this->m_rMagnetometerAccuracy <= CIMUTracker::s_rMaxMagCorrectionAccuracy) {
			this->calculateLiveMagnetometerCorrection();
		}
	}
}