#pragma once

#include "NodePosition.h"
#include "TransformNode.h"
#include "ComputedHumanPoseTracker.h"
#include <map>
#include <library/Mutex.h>
#include <library/LockGuard.h>

namespace VRProcessor {
	class CSimpleSkeleton
	{
	public:
		CSimpleSkeleton();
		virtual ~CSimpleSkeleton();
	public:
		void setComputedTracker(std::shared_ptr<VRTracker::CComputedHumanPoseTracker> i_pTracker);
	private:
		void fillNullComputedTrackers(bool i_bFillAll);
		void fillTrackerIfNotSet(VRTracker::ETrackerRole i_eRole, VRTracker::ETrackerPosition i_ePosition, const std::string_view i_stName);		
		bool getTrackerRotation(VRTracker::ETrackerPosition i_ePosition, QQuaternion& i_oRotation);
		bool getTrackerPosition(VRTracker::ETrackerPosition i_ePosition, QVector3D& i_oPosition);
		void updateComputedTracker(std::shared_ptr<VRTracker::CComputedHumanPoseTracker> i_pTracker, ENodePosition i_ePositionNode, ENodePosition i_eRotationNode);
	private:
		void updateLocalTransforms();
		void updateRootNodes();
		void updateComputedTrackers();
	public:
		void setTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CTracker> i_pTracker);
		void updatePose();
	public:
		std::shared_ptr<VRTracker::CComputedHumanPoseTracker> getTrackerByRole(VRTracker::ETrackerRole i_eRole) {
			RecursiveLockGuard(this->m_oMutex);
			return this->m_apComputedTracker[i_eRole];
		}
	private:
		CMutex m_oMutex;
		std::map<ENodePosition, CTransformNode> m_aoNodes;
		std::map<VRTracker::ETrackerRole, std::shared_ptr<VRTracker::CComputedHumanPoseTracker>> m_apComputedTracker;
		std::map<VRTracker::ETrackerPosition, std::shared_ptr<VRTracker::CTracker>> m_apTracker;
	};
}