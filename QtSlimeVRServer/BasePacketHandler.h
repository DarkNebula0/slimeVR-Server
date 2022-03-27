#pragma once
#include "Defines.h"
#include "Logger.h"
#include "../Core/PacketBase.h"
#include <library/ThreadPool.h>
#include <library/NetworkPacket.h>
#include <functional>
#include <memory>
#include <map>

namespace Network
{
	namespace Packet
	{
		template<typename TSession>
		using fnFunctionBase = std::function<void(const std::shared_ptr<TSession> &, const CNetworkPacket &)>;
		
		template<typename TSession>
		struct SOperation
		{
		public:
			uint32_t nID;
			fnFunctionBase<TSession> fnFunction;
		public:
			SOperation() : nID(0) {}
			SOperation(const SOperation& i_oOther)
			{
				this->nID = i_oOther.nID;
				this->fnFunction = i_oOther.nID;
			}
			SOperation(SOperation<TSession> &&i_oOther) noexcept
				{ this->operator=(i_oOther); }
			virtual ~SOperation() = default;
		public:
			SOperation<TSession> &operator=(SOperation<TSession> &&i_oOther) noexcept
			{
				nID = i_oOther.nID;
				fnFunction = std::move(i_oOther.fnFunction);
				return *this;
			}
		};

		template<typename TSession>
		class CBaseHandler
		{
		public:
			CBaseHandler();
			virtual ~CBaseHandler();
		private:
			std::map<uint32_t, SOperation<TSession>> m_afnPacket;
		private:
			CThreadPool *m_pPool;
		public:
			void handle(std::shared_ptr<TSession> i_pSession, const CNetworkPacket &i_oPacket, const bool i_bDectypt = false);
			void createPool(const size_t i_nWorkerCount);
		public:
			_inline void addPacketOperation(SOperation<TSession> &i_grOperation)
			{
				this->m_afnPacket[i_grOperation.nID] = std::move(i_grOperation);
			}
		public:
			_inline void closePool()
			{
				if (this->m_pPool)
				{
					this->m_pPool->stop(true);
				}
			}
			_inline void addTask(std::shared_ptr<TSession> i_pSession, const CNetworkPacket &i_oPacket, const bool i_bDectypt = false)
			{
				if (this->m_pPool)
				{
					this->m_pPool->addTask(std::bind(&CBaseHandler::handle, this, i_pSession, std::move(i_oPacket), i_bDectypt));
				}
			}
		};
	}
}


template<typename TSession>
Network::Packet::CBaseHandler<TSession>::CBaseHandler()
	: m_pPool(nullptr)
{}

template<typename TSession>
Network::Packet::CBaseHandler<TSession>::~CBaseHandler()
{
	delete this->m_pPool;
}

template<typename TSession>
void Network::Packet::CBaseHandler<TSession>::createPool(const size_t i_nWorkerCount)
{
	if (!this->m_pPool)
	{
		this->m_pPool = new CThreadPool(i_nWorkerCount);
		this->m_pPool->execute();
	}
}

template<typename TSession>
void Network::Packet::CBaseHandler<TSession>::handle(std::shared_ptr<TSession> i_pSession, const CNetworkPacket &i_oPacket, const bool i_bDectypt)
{
	const uint16_t shLength = static_cast<uint16_t>(i_oPacket.size());
	uint16_t shCursorPos = 0;

	while (shLength - shCursorPos >= sizeof(SPacketHeader<>) && shCursorPos < shLength)
	{
		const char *pPointer = i_oPacket.buffer() + shCursorPos;
		const SPacketHeader<> *pHeader = reinterpret_cast<const SPacketHeader<>*>(pPointer);

		if (pHeader->length() >= 4 || shLength - shCursorPos >= pHeader->length())
		{
			if (pHeader->verifier() == 0xF0)
			{
				const SOperation<TSession> &grOperation = this->m_afnPacket[pHeader->id()];
				if (grOperation.fnFunction)
				{
					grOperation.fnFunction(i_pSession, CNetworkPacket(i_oPacket.buffer() + shCursorPos, pHeader->length(), false, false));	
				}
				else
				{
					LOGW_DEBUG("PacketHandler-Function [" + std::string(typeid(TSession).name()) + "] Handler not found! ID: " + Utils::ToHexString<uint32_t>(pHeader->id()));
				}
			}
			else
			{
				LOGE("PacketHandler-Function Invalid verifier");
				i_pSession->close();
				break;
			}
			shCursorPos += pHeader->length();
		}
		else
		{
			LOGE("PacketHandler-Function Packet is not big enough!");
			i_pSession->close();
			break;	
		}
	}
}