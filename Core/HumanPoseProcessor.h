#pragma once
#include <library/MutexVector.h>
#include <library/Singleton.h>
#include <library/Mutex.h>
#include <memory>
#include <string>
#include <map>

// TODO: Add imu from network packet [udp]
// Handshake pack.

namespace VRTracker {
	class CComputedHumanPoseTracker;
	class CVRTracker;
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
		void addVRTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CVRTracker> i_pTracker);
	public:
		__inline std::shared_ptr<VRTracker::CVRTracker> getVRTrackerById(uint32_t i_nId) {
			return this->m_apVRTrackerById[i_nId];
		}
	private:
		CSimpleSkeleton* m_pSkeleton;
		CMutexVector<std::shared_ptr<VRTracker::CComputedHumanPoseTracker>> m_apTracker;
		CMutex m_oMutex;
		std::map<VRTracker::ETrackerPosition, std::shared_ptr<VRTracker::CVRTracker>> m_apVRTracker;
		std::map<uint32_t, std::shared_ptr<VRTracker::CVRTracker>> m_apVRTrackerById;
		bool m_bIsInitialized;
	};
}
extern VRProcessor::CHumanPoseProcessor* HumanPoseProcessorInstance;