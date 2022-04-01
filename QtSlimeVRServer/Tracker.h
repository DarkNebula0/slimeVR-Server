#pragma once

#include <../Core/IMUTracker.h>

#include <string>
#include <library/CharArray.h>
#include <library/Timer.h>
#include <memory>

class CTracker
{
public:
	CTracker();
	virtual ~CTracker() = default;
public:
	enum class EImu : uint32_t {
		NONE = 0x00,
		IMU_ICM20948 = 0x01,
		IMU_MPU6050 = 0x02,
	};

	enum class EEmuState : uint8_t {
		SENSOR_OFFLINE = 0x00,
		SENSOR_OK,
		SENSOR_ERROR
	};

	struct SInfo
	{
		EImu eIMU0;
		EImu eIMU1;
		EEmuState eIMUState0;
		EEmuState eIMUState1;
		CCharArray<6> chMAC;
		SInfo() 
			: eIMU0(EImu::NONE), eIMU1(EImu::NONE)
			, eIMUState0(EEmuState::SENSOR_OFFLINE)
			, eIMUState1(EEmuState::SENSOR_OFFLINE)
		{}
	};
private:
	SInfo m_grInfo;
	bool m_bIsReady;
	int8_t m_nRSSI;
	std::shared_ptr<VRTracker::CIMUTracker> m_pTracker0;
	std::shared_ptr<VRTracker::CIMUTracker> m_pTracker1;
public:
	__inline SInfo& info() { return this->m_grInfo; }
	__inline bool isReady() const { return this->m_bIsReady; }
	__inline int8_t rssi() const { return this->m_nRSSI; }
	std::shared_ptr<VRTracker::CIMUTracker> imuTrackerById(uint32_t i_nId);
public:
	__inline void setReady() { this->m_bIsReady = true; }
	__inline void setRSSI(const int8_t i_nRSSI) {
		this->m_nRSSI = i_nRSSI;
	}
	void setImuTracker(uint32_t i_nId, std::shared_ptr<VRTracker::CIMUTracker> i_pTracker);
};