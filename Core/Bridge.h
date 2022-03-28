#pragma once

#include "ProtobufMessages.pb.h"
#include <Windows.h>
#include <library/Singleton.h>
#include <library/Mutex.h>

namespace VRDriver {

	enum class EBridgeState : uint32_t {
		Disconnected = 0x00,
		Connected,
		Error,
	};

	class CBridge : public CSingleton<CBridge>
	{
		friend CSingleton<CBridge>;
	private:
		CBridge();
		~CBridge() { this->close(); };
	private:
		HANDLE m_pPipeHandle;
		EBridgeState m_eState;
		CMutex m_oMutex;
	public:
		__inline EBridgeState state() {
			return this->m_eState;
		}
	public:
		void initialize();
		void update();
		EBridgeState open();
		EBridgeState close();
		EBridgeState reset();
	public:
		bool getNextMessage(messages::ProtobufMessage* i_pMsg);
		bool sendMessage(messages::ProtobufMessage* i_pMsg);
	};
};

extern VRDriver::CBridge* BridgeInstance;