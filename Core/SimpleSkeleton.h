#pragma once

#include "NodePosition.h"
#include "TransformNode.h"
#include "ComputedHumanPoseTracker.h"
#include <map>
#include <library/MutexVector.h>

namespace VRProcessor {
	class CSimpleSkeleton
	{
	public:
		CSimpleSkeleton();
		virtual ~CSimpleSkeleton();
	public:
		void setComputedTracker(VRTracker::CComputedHumanPoseTracker i_oTracker);
	private:
		std::map<ENodePosition, CTransformNode> m_aoNodes;
		CMutexVector<VRTracker::CComputedHumanPoseTracker> m_aoComputedTracker;
	};
}