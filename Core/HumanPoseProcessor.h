#pragma once
#include <library/MutexVector.h>
#include <library/Singleton.h>
#include <library/Mutex.h>
#include <memory>
#include <string>
#include <map>

namespace VRTracker {
	class CComputedHumanPoseTracker;
	class CTracker;
	class CVRTracker;
	class CIMUTracker;
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
		void updatePose();
		void addVRTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CVRTracker> i_pTracker);
		void addSensorTracker(std::shared_ptr<VRTracker::CIMUTracker> i_pTracker);
		void removeSensorTracker(std::shared_ptr<VRTracker::CIMUTracker> i_pTracker);
		void setSkeletonTracker(VRTracker::ETrackerPosition i_ePosition, std::shared_ptr<VRTracker::CTracker> i_pTracker);
	public:
		__inline std::shared_ptr<VRTracker::CVRTracker> getVRTrackerById(uint32_t i_nId) {
			return this->m_apVRTrackerById[i_nId];
		}
	private:
		CSimpleSkeleton* m_pSkeleton;
		CMutexVector<std::shared_ptr<VRTracker::CComputedHumanPoseTracker>> m_apTracker;
		CMutexVector<std::shared_ptr<VRTracker::CIMUTracker>> m_apSensorTracker;
		CMutex m_oMutex;
		std::map<VRTracker::ETrackerPosition, std::shared_ptr<VRTracker::CVRTracker>> m_apVRTracker;
		std::map<uint32_t, std::shared_ptr<VRTracker::CVRTracker>> m_apVRTrackerById;
		bool m_bIsInitialized;
	};
}
extern VRProcessor::CHumanPoseProcessor* HumanPoseProcessorInstance;