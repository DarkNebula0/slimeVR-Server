#include "SimpleSkeleton.h"
#include <library/LockGuard.h>

VRProcessor::CSimpleSkeleton::CSimpleSkeleton()
{
	// Assemble nodes it's almost like playing pussel

	// Head to hip
	this->m_aoNodes[ENodePosition::Hmd].addChild(this->m_aoNodes[ENodePosition::Head].shared_from_this());
	this->m_aoNodes[ENodePosition::Head].addChild(this->m_aoNodes[ENodePosition::Neck].shared_from_this());
	this->m_aoNodes[ENodePosition::Neck].addChild(this->m_aoNodes[ENodePosition::Chest].shared_from_this());
	this->m_aoNodes[ENodePosition::Chest].addChild(this->m_aoNodes[ENodePosition::Waist].shared_from_this());
	this->m_aoNodes[ENodePosition::Waist].addChild(this->m_aoNodes[ENodePosition::Hip].shared_from_this());

	// Hip to feet 
	this->m_aoNodes[ENodePosition::Hip].addChild(this->m_aoNodes[ENodePosition::LeftHip].shared_from_this());
	this->m_aoNodes[ENodePosition::Hip].addChild(this->m_aoNodes[ENodePosition::RightHip].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftHip].addChild(this->m_aoNodes[ENodePosition::LeftKnee].shared_from_this());
	this->m_aoNodes[ENodePosition::RightHip].addChild(this->m_aoNodes[ENodePosition::RightKnee].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftKnee].addChild(this->m_aoNodes[ENodePosition::LeftAnkle].shared_from_this());
	this->m_aoNodes[ENodePosition::RightKnee].addChild(this->m_aoNodes[ENodePosition::RightAnkle].shared_from_this());
	this->m_aoNodes[ENodePosition::RightAnkle].addChild(this->m_aoNodes[ENodePosition::LeftFoot].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftAnkle].addChild(this->m_aoNodes[ENodePosition::RightFoot].shared_from_this());

	// Arms
	this->m_aoNodes[ENodePosition::LeftHand].addChild(this->m_aoNodes[ENodePosition::LeftWrist].shared_from_this());
	this->m_aoNodes[ENodePosition::RightHand].addChild(this->m_aoNodes[ENodePosition::RightWrist].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftWrist].addChild(this->m_aoNodes[ENodePosition::LeftElbow].shared_from_this());
	this->m_aoNodes[ENodePosition::RightWrist].addChild(this->m_aoNodes[ENodePosition::RightElbow].shared_from_this());

	// Offsets
	this->m_aoNodes[ENodePosition::Chest].addChild(this->m_aoNodes[ENodePosition::ChestTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::Hip].addChild(this->m_aoNodes[ENodePosition::WaistTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftKnee].addChild(this->m_aoNodes[ENodePosition::LeftKneeTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::RightKnee].addChild(this->m_aoNodes[ENodePosition::RightKneeTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftFoot].addChild(this->m_aoNodes[ENodePosition::LeftFootTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::RightFoot].addChild(this->m_aoNodes[ENodePosition::RightFootTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::LeftElbow].addChild(this->m_aoNodes[ENodePosition::LeftElbowTracker].shared_from_this());
	this->m_aoNodes[ENodePosition::RightElbow].addChild(this->m_aoNodes[ENodePosition::RightElbowTracker].shared_from_this());
}

VRProcessor::CSimpleSkeleton::~CSimpleSkeleton()
{}

void VRProcessor::CSimpleSkeleton::setComputedTracker(VRTracker::CComputedHumanPoseTracker i_oTracker)
{
	// TODO: Add move constructor to CComputedHumanPoseTracker
	MutexVectorLockGuard(this->m_aoComputedTracker);
	switch (i_oTracker.trackerRole()->role())
	{
	case VRTracker::ETrackerRole::Waist:
	case VRTracker::ETrackerRole::LeftFoot:
	case VRTracker::ETrackerRole::RightFoot:
	case VRTracker::ETrackerRole::Chest:
	case VRTracker::ETrackerRole::LeftKnee:
	case VRTracker::ETrackerRole::RightKnee:
	case VRTracker::ETrackerRole::LeftElbow:
	case VRTracker::ETrackerRole::RightElbow:
		this->m_aoComputedTracker.push_back(std::move(i_oTracker));
		break;
	default:
		break;
	}
}