#include "HumanPoseProcessor.h"
#include "SimpleSkeleton.h"
#include "ComputedHumanPoseTracker.h"
#include "VRTracker.h"
#include <library/LockGuard.h>

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
	this->m_pSkeleton->setTracker(i_oPosition, std::dynamic_pointer_cast<VRTracker::CTracker>(pTracker));
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

void VRProcessor::CHumanPoseProcessor::addVRTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CVRTracker> i_pTracker)
{
	if (!i_pTracker) {
		return;
	}

	RecursiveLockGuard(this->m_oMutex);
	this->m_apVRTracker[i_ePosition] = i_pTracker;
	this->m_apVRTrackerById[i_pTracker->id()] = i_pTracker;
}