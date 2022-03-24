#pragma once

#include <string>
#include "CharArray.h"

class CTracker
{
public:
	CTracker();
	virtual ~CTracker() = default;
public:
	enum EImu : uint32_t {
		IMU_ICM20948 = 0x00,
	};

	struct SInfo
	{
		EImu eIMU;
		CCharArray<6> chMAC;
	};
private:
	SInfo m_grInfo;
	bool m_bIsReady;
	int8_t m_nRSSI;
public:
	__inline SInfo& info() { return this->m_grInfo; }
	__inline bool isReady() const { return this->m_bIsReady; }
	__inline int8_t rssi() const { return this->m_nRSSI; }
public:
	__inline void setReady() { this->m_bIsReady = true; }
	__inline void setRSSI(const int8_t i_nRSSI) {
		this->m_nRSSI = i_nRSSI;
	}

};