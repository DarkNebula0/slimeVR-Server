#pragma once
#include "ProtobufMessages.pb.h"

#include <library/Singleton.h>
#include <functional>
#include <memory>
#include <map>

class CThreadPool;
namespace VRDriver {
	using fnFunctionBase = std::function<void(const messages::ProtobufMessage&)>;
	class CBridgeHandler: public CSingleton<CBridgeHandler>
	{
		friend CSingleton<CBridgeHandler>;
	private:
		CBridgeHandler();
		~CBridgeHandler();
	private:
		std::map<uint32_t, fnFunctionBase> m_afnPacket;
		CThreadPool* m_pPool;
	private:
		void handle(const messages::ProtobufMessage& i_oMessage);
	public:
		void createPool(const size_t i_nWorkerCount);
		void closePool();
	public:
		_inline void addMessageOperation(uint32_t i_nId, fnFunctionBase &i_fnHandler)
		{
			this->m_afnPacket[i_nId] = std::move(i_fnHandler);
		}
	};
}
