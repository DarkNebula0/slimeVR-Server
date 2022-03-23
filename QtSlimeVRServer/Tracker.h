#pragma once

#include <string>
#include "CharArray.h"

class CTracker
{
public:
	CTracker() = default;
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
public:
	__inline SInfo& info() { return this->m_grInfo; }
public:
	__inline bool isReady() { return this->m_bIsReady; }
};