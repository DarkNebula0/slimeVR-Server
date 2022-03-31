#pragma once
#include <library/MutexVector.h>
#include <library/Singleton.h>
#include <memory>
#include <string>

namespace VRTracker {
	class CComputedHumanPoseTracker;
	enum class ETrackerPosition;
}

namespace VRProcessor {
	class CSimpleSkeleton;
	class CHumanPoseProcessor : public CSingleton<CHumanPoseProcessor>
	{
		friend CSingleton<CHumanPoseProcessor>;
	private:
		CHumanPoseProcessor() : m_bIsInitialized(false) {};
		virtual ~CHumanPoseProcessor();
	private:
		void addTracker(const std::string_view i_stName, VRTracker::ETrackerPosition i_oPosition);
	public:
		void initialize();
	private:
		CSimpleSkeleton* m_pSkeleton;
		CMutexVector<std::shared_ptr<VRTracker::CComputedHumanPoseTracker>> m_apTracker;
		bool m_bIsInitialized;
	};
}
extern VRProcessor::CHumanPoseProcessor* HumanPoseProcessorInstance;