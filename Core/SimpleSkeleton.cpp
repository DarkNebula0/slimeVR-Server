#include "SimpleSkeleton.h"

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

void VRProcessor::CSimpleSkeleton::setComputedTracker(std::shared_ptr<VRTracker::CComputedHumanPoseTracker> i_pTracker)
{
	RecursiveLockGuard(this->m_oMutex);
	switch (i_pTracker->trackerRole()->role())
	{
	case VRTracker::ETrackerRole::Waist:
	case VRTracker::ETrackerRole::LeftFoot:
	case VRTracker::ETrackerRole::RightFoot:
	case VRTracker::ETrackerRole::Chest:
	case VRTracker::ETrackerRole::LeftKnee:
	case VRTracker::ETrackerRole::RightKnee:
	case VRTracker::ETrackerRole::LeftElbow:
	case VRTracker::ETrackerRole::RightElbow:
		this->m_apComputedTracker[i_pTracker->trackerRole()->role()] = i_pTracker;
		break;
	default:
		break;
	}
}

void VRProcessor::CSimpleSkeleton::fillTrackerIfNotSet(VRTracker::ETrackerRole i_eRole, VRTracker::ETrackerPosition i_ePosition, const std::string_view i_stName)
{
	RecursiveLockGuard(this->m_oMutex);
	if (!this->m_apComputedTracker[i_eRole]) {
		this->m_apComputedTracker[i_eRole] = std::make_shared<VRTracker::CComputedHumanPoseTracker>(i_stName, i_ePosition);
		this->m_apComputedTracker[i_eRole]->setStatus(VRTracker::ETrackerStatus::Ok);
	}
}

void VRProcessor::CSimpleSkeleton::setTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CTracker> i_pTracker)
{
	RecursiveLockGuard(this->m_oMutex);
	this->m_apTracker[i_ePosition] = i_pTracker;
}

bool VRProcessor::CSimpleSkeleton::getTrackerRotation(VRTracker::ETrackerPosition i_ePosition, QQuaternion& i_oRotation)
{
	RecursiveLockGuard(this->m_oMutex);
	if (this->m_apTracker[i_ePosition]) {
		return this->m_apTracker[i_ePosition]->rotation(i_oRotation);
	}

	return false;
}

bool VRProcessor::CSimpleSkeleton::getTrackerPosition(VRTracker::ETrackerPosition i_ePosition, QVector3D& i_oPosition)
{
	RecursiveLockGuard(this->m_oMutex);
	if (this->m_apTracker[i_ePosition]) {
		return this->m_apTracker[i_ePosition]->position(i_oPosition);
	}

	return false;
}

void VRProcessor::CSimpleSkeleton::updateComputedTracker(std::shared_ptr<VRTracker::CComputedHumanPoseTracker> i_pTracker, ENodePosition i_ePositionNode, ENodePosition i_eRotationNode)
{
	if (!i_pTracker) return;
	RecursiveLockGuard(this->m_oMutex);
	i_pTracker->setPosition(this->m_aoNodes[i_ePositionNode].worldTransform()->translation());
	i_pTracker->setRotation(this->m_aoNodes[i_eRotationNode].worldTransform()->rotation());
	i_pTracker->dataTick();
}

void VRProcessor::CSimpleSkeleton::updateLocalTransforms()
{
	RecursiveLockGuard(this->m_oMutex);
	QVector3D oPosition(0.0f, 0.0f, 0.0f);
	QQuaternion oRotation(0.0f, 0.0f, 0.0f, 1.0f);
	QQuaternion oRotation2(0.0f, 0.0f, 0.0f, 1.0f);

	// Hmd tracker 
	if (this->m_apTracker[VRTracker::ETrackerPosition::Hmd]) {
		if (this->m_apTracker[VRTracker::ETrackerPosition::Hmd]->position(oPosition)) {
			this->m_aoNodes[ENodePosition::Hmd].localTransform()->setTranslation(oPosition);
		}
		if (this->getTrackerRotation(VRTracker::ETrackerPosition::Hmd, oRotation)) {
			this->m_aoNodes[ENodePosition::Hmd].localTransform()->setRotation(oRotation);
			this->m_aoNodes[ENodePosition::Head].localTransform()->setRotation(oRotation);
		}
	}
	else {
		this->m_aoNodes[ENodePosition::Hmd].localTransform()->setTranslation(oPosition);
		this->m_aoNodes[ENodePosition::Hmd].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::Head].localTransform()->setRotation(oRotation);
	}

	// Chest tracker
	if (this->getTrackerRotation(VRTracker::ETrackerPosition::Chest, oRotation)) {
		this->m_aoNodes[ENodePosition::Neck].localTransform()->setRotation(oRotation);
	}

	// Waist tracker
	if (this->getTrackerRotation(VRTracker::ETrackerPosition::Waist, oRotation)) {
		this->m_aoNodes[ENodePosition::Chest].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::ChestTracker].localTransform()->setRotation(oRotation);
	}

	// Hip tracker
	if (this->getTrackerRotation(VRTracker::ETrackerPosition::Hip, oRotation)) {
		this->m_aoNodes[ENodePosition::Waist].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::WaistTracker].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::Hip].localTransform()->setRotation(oRotation);
	}

	// Left leg
	this->getTrackerRotation(VRTracker::ETrackerPosition::LeftLeg, oRotation);
	this->getTrackerRotation(VRTracker::ETrackerPosition::LeftAnkle, oRotation2);

	this->m_aoNodes[ENodePosition::LeftHip].localTransform()->setRotation(oRotation);
	this->m_aoNodes[ENodePosition::LeftKnee].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::LeftAnkle].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::LeftFoot].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::LeftKneeTracker].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::LeftFootTracker].localTransform()->setRotation(oRotation2);

	if (this->getTrackerRotation(VRTracker::ETrackerPosition::LeftFoot, oRotation2)) {
		this->m_aoNodes[ENodePosition::LeftAnkle].localTransform()->setRotation(oRotation2);
		this->m_aoNodes[ENodePosition::LeftFoot].localTransform()->setRotation(oRotation2);
		this->m_aoNodes[ENodePosition::LeftFootTracker].localTransform()->setRotation(oRotation2);
	}

	// Right leg 
	this->getTrackerRotation(VRTracker::ETrackerPosition::RightLeg, oRotation);
	this->getTrackerRotation(VRTracker::ETrackerPosition::RightAnkle, oRotation2);

	this->m_aoNodes[ENodePosition::RightHip].localTransform()->setRotation(oRotation);
	this->m_aoNodes[ENodePosition::RightKnee].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::RightAnkle].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::RightFoot].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::RightKneeTracker].localTransform()->setRotation(oRotation2);
	this->m_aoNodes[ENodePosition::RightFootTracker].localTransform()->setRotation(oRotation2);

	if (this->getTrackerRotation(VRTracker::ETrackerPosition::RightFoot, oRotation2)) {
		this->m_aoNodes[ENodePosition::RightAnkle].localTransform()->setRotation(oRotation2);
		this->m_aoNodes[ENodePosition::RightFoot].localTransform()->setRotation(oRotation2);
		this->m_aoNodes[ENodePosition::RightFootTracker].localTransform()->setRotation(oRotation2);
	}

	// Left arm 
	if (this->m_apTracker[VRTracker::ETrackerPosition::LeftHand]) {
		if (this->getTrackerPosition(VRTracker::ETrackerPosition::LeftHand, oPosition)) {
			this->m_aoNodes[ENodePosition::LeftHand].localTransform()->setTranslation(oPosition);
		}
		if (this->getTrackerRotation(VRTracker::ETrackerPosition::LeftHand, oRotation)) {
			this->m_aoNodes[ENodePosition::LeftHand].localTransform()->setRotation(oRotation);
		}
	}

	if (this->getTrackerRotation(VRTracker::ETrackerPosition::LeftElbow, oRotation)) {
		this->m_aoNodes[ENodePosition::LeftWrist].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::LeftElbowTracker].localTransform()->setRotation(oRotation);
	}

	// Right arm 
	if (this->m_apTracker[VRTracker::ETrackerPosition::RightHand]) {
		if (this->getTrackerPosition(VRTracker::ETrackerPosition::RightHand, oPosition)) {
			this->m_aoNodes[ENodePosition::RightHand].localTransform()->setTranslation(oPosition);
		}
		if (this->getTrackerRotation(VRTracker::ETrackerPosition::RightHand, oRotation)) {
			this->m_aoNodes[ENodePosition::RightHand].localTransform()->setRotation(oRotation);
		}
	}

	if (this->getTrackerRotation(VRTracker::ETrackerPosition::RightElbow, oRotation)) {
		this->m_aoNodes[ENodePosition::RightWrist].localTransform()->setRotation(oRotation);
		this->m_aoNodes[ENodePosition::RightElbowTracker].localTransform()->setRotation(oRotation);
	}
}

void VRProcessor::CSimpleSkeleton::updateRootNodes()
{
	RecursiveLockGuard(this->m_oMutex);
	this->m_aoNodes[ENodePosition::Hmd].update();
	this->m_aoNodes[ENodePosition::LeftHand].update();
	this->m_aoNodes[ENodePosition::RightHand].update();
}

void VRProcessor::CSimpleSkeleton::updateComputedTrackers()
{
	RecursiveLockGuard(this->m_oMutex);
	for (auto const& [eKey, pTracker] : this->m_apComputedTracker) {
		if (!pTracker) { continue; }
		switch (eKey)
		{
		case VRTracker::ETrackerRole::Waist:
			this->updateComputedTracker(pTracker, ENodePosition::Waist, ENodePosition::Waist);
			break;
		case VRTracker::ETrackerRole::LeftFoot:
			this->updateComputedTracker(pTracker, ENodePosition::LeftFootTracker, ENodePosition::LeftFootTracker);
			break;
		case VRTracker::ETrackerRole::RightFoot:
			this->updateComputedTracker(pTracker, ENodePosition::RightFoot, ENodePosition::RightFoot);
			break;
		case VRTracker::ETrackerRole::Chest:
			this->updateComputedTracker(pTracker, ENodePosition::ChestTracker, ENodePosition::Neck);
			break;
		case VRTracker::ETrackerRole::LeftKnee:
			this->updateComputedTracker(pTracker, ENodePosition::LeftKneeTracker, ENodePosition::LeftHip);
			break;
		case VRTracker::ETrackerRole::RightKnee:
			this->updateComputedTracker(pTracker, ENodePosition::RightKneeTracker, ENodePosition::RightHip);
			break;
		case VRTracker::ETrackerRole::LeftElbow:
			this->updateComputedTracker(pTracker, ENodePosition::LeftElbowTracker, ENodePosition::LeftElbowTracker);
			break;
		case VRTracker::ETrackerRole::RightElbow:
			this->updateComputedTracker(pTracker, ENodePosition::RightElbowTracker, ENodePosition::RightElbowTracker);
			break;
		default:
			break;
		}
	}
}


void VRProcessor::CSimpleSkeleton::updatePose()
{
	this->updateLocalTransforms();
	this->updateRootNodes();
	this->updateComputedTrackers();
}

void VRProcessor::CSimpleSkeleton::fillNullComputedTrackers(bool i_bFillAll)
{
	fillTrackerIfNotSet(VRTracker::ETrackerRole::Waist, VRTracker::ETrackerPosition::Waist, "Waist");
	fillTrackerIfNotSet(VRTracker::ETrackerRole::LeftFoot, VRTracker::ETrackerPosition::LeftFoot, "LeftFoot");
	fillTrackerIfNotSet(VRTracker::ETrackerRole::RightFoot, VRTracker::ETrackerPosition::RightFoot, "RightFoot");

	if (i_bFillAll) {
		fillTrackerIfNotSet(VRTracker::ETrackerRole::Chest, VRTracker::ETrackerPosition::Chest, "Chest");
		fillTrackerIfNotSet(VRTracker::ETrackerRole::LeftKnee, VRTracker::ETrackerPosition::LeftLeg, "LeftKnee");
		fillTrackerIfNotSet(VRTracker::ETrackerRole::RightKnee, VRTracker::ETrackerPosition::RightLeg, "RightKnee");
		fillTrackerIfNotSet(VRTracker::ETrackerRole::LeftElbow, VRTracker::ETrackerPosition::LeftElbow, "LeftElbow");
		fillTrackerIfNotSet(VRTracker::ETrackerRole::RightElbow, VRTracker::ETrackerPosition::RightElbow, "LeftElbow");
	}
}
