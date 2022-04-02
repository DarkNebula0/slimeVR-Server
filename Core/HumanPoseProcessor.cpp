#include "HumanPoseProcessor.h"
#include "SimpleSkeleton.h"
#include "ComputedHumanPoseTracker.h"
#include "IMUTracker.h"
#include "VRTracker.h"
#include "BridgeSend.h"
#include <library/Logger.h>
#include <library/LockGuard.h>
#include <string>


template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

VRProcessor::CHumanPoseProcessor* HumanPoseProcessorInstance = VRProcessor::CHumanPoseProcessor::instance();

VRProcessor::CHumanPoseProcessor::~CHumanPoseProcessor()
{
	if (this->m_pSkeleton) {
		delete this->m_pSkeleton;
	}
}

void VRProcessor::CHumanPoseProcessor::addTracker(const std::string_view i_stName, VRTracker::ETrackerPosition i_oPosition)
{
	auto pTracker = std::make_shared<VRTracker::CComputedHumanPoseTracker>(i_stName, i_oPosition);
	pTracker->setBodyPosition(i_oPosition);
	this->m_pSkeleton->setComputedTracker(i_oPosition, pTracker);
	MutexVectorLockGuard(this->m_apTracker);
	this->m_apTracker.push_back(pTracker);
}

void VRProcessor::CHumanPoseProcessor::initialize()
{
	if (this->m_bIsInitialized) {
		return;
	}

	this->m_pSkeleton = new CSimpleSkeleton();

	this->addTracker("Waist", VRTracker::ETrackerPosition::Waist);
	this->addTracker("LeftFoot", VRTracker::ETrackerPosition::LeftFoot);
	this->addTracker("RightFoot", VRTracker::ETrackerPosition::RightFoot);
	this->addTracker("Chest", VRTracker::ETrackerPosition::Chest);
	this->addTracker("LeftLeg", VRTracker::ETrackerPosition::LeftLeg);
	this->addTracker("RightLeg", VRTracker::ETrackerPosition::RightLeg);
	this->addTracker("LeftElbow", VRTracker::ETrackerPosition::LeftElbow);
	this->addTracker("RightElbow", VRTracker::ETrackerPosition::RightElbow);

	this->m_bIsInitialized = true;
}

void VRProcessor::CHumanPoseProcessor::updatePose()
{
	if (!this->m_bIsInitialized) {
		return;
	}

	this->m_pSkeleton->updatePose();

	MutexVectorLockGuard(this->m_apSensorTracker);
	for (auto pSensorTracker : this->m_apSensorTracker) {
		auto pComputedTracker = this->m_pSkeleton->getTrackerByRole(VRTracker::s_aoTrackerPosition[pSensorTracker->bodyPosition()->position()].role().role());
		if (pComputedTracker) {
			QQuaternion oRot;
			QVector3D oPos;
			pComputedTracker->rotation(oRot);
			pComputedTracker->position(oPos);
			auto xx = std::string(VRTracker::s_aoTrackerPosition[pSensorTracker->bodyPosition()->position()].role().viveRole());
			auto x = string_format("New computed tracker result: Role: %s  Position {x:%f,y:%f,z:%f} Rotation {x:%f,y:%f,z:%f,w:%f}", 
				xx.c_str(), oPos.x(), oPos.y(), oPos.z(), oRot.x(), oRot.y(), oRot.z(), oRot.scalar());
			LOGI_DEBUG(x);
		}
	}

}

void VRProcessor::CHumanPoseProcessor::addVRTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CVRTracker> i_pTracker)
{
	if (!i_pTracker) {
		return;
	}

	// Todo: rewrite
	if (i_pTracker->bodyPosition()->position() == VRTracker::ETrackerPosition::Hmd) {
		this->setSkeletonTracker(VRTracker::ETrackerPosition::Hmd, std::dynamic_pointer_cast<VRTracker::CTracker>(i_pTracker));
	}

	RecursiveLockGuard(this->m_oMutex);
	this->m_apVRTracker[i_ePosition] = i_pTracker;
	this->m_apVRTrackerById[i_pTracker->id()] = i_pTracker;
}

void VRProcessor::CHumanPoseProcessor::addSensorTracker(std::shared_ptr<VRTracker::CIMUTracker> i_pTracker)
{
	MutexVectorLockGuard(this->m_apSensorTracker);
	this->m_apSensorTracker.push_back(i_pTracker);
}

void VRProcessor::CHumanPoseProcessor::removeSensorTracker(std::shared_ptr<VRTracker::CIMUTracker> i_pTracker)
{
	MutexVectorLockGuard(this->m_apSensorTracker);
	this->m_apSensorTracker.remove(i_pTracker);
}

void VRProcessor::CHumanPoseProcessor::setSkeletonTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CTracker> i_pTracker)
{
	LOGI_DEBUG("Add tracker to skeleton position:" + std::string(VRTracker::s_aoTrackerPosition[i_ePosition].designation()));
	this->m_pSkeleton->setTracker(i_ePosition, i_pTracker);
}
