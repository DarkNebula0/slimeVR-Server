#pragma once
#include "PacketBase.h"
#include "Logger.h"

#include <QThreadPool>
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
			byte chID;
			fnFunctionBase<TSession> fnFunction;
		public:
			SOperation() : chID(0) {}
			SOperation(const SOperation& i_oOther)
			{
				this->chID = i_oOther.chID;
				this->fnFunction = i_oOther.chID;
			}
			SOperation(SOperation<TSession> &&i_oOther) noexcept
				{ this->operator=(i_oOther); }
			virtual ~SOperation() = default;
		public:
			SOperation<TSession> &operator=(SOperation<TSession> &&i_oOther) noexcept
			{
				chID = i_oOther.chID;
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
			std::map<byte, SOperation<TSession>> m_afnPacket;
		private:
			QThreadPool *m_pPool;
		public:
			void handle(std::shared_ptr<TSession> i_pSession, const CNetworkPacket &i_oPacket, const bool i_bDectypt = false);
			void createPool(const size_t i_nWorkerCount);
		public:
			_inline void addPacketOperation(SOperation<TSession> &i_grOperation)
			{
				this->m_afnPacket[i_grOperation.chID] = std::move(i_grOperation);
			}
			_inline void removePacketOperation(const byte i_chID)
			{
				this->m_afnPacket[i_chID] = nullptr;
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
	if (!i_pSession->isValid())
		return;

	const ushort shLength = static_cast<ushort>(i_oPacket.size());
	ushort shCursorPos = 0;

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
					if (i_bDectypt)
					{
						GameCrypt::DecryptPacket(const_cast<char *>(i_oPacket.buffer() + shCursorPos), pHeader->length());
					}
					
					grOperation.fnFunction(i_pSession, CNetworkPacket(i_oPacket.buffer() + shCursorPos, pHeader->length(), false, false));	
				}
				else
				{
					LOGW_DEBUG("PacketHandler-Function [" + std::string(typeid(TSession).name()) + "] Handler not found! ID: " + Utils::ToHexString<byte>(pHeader->id()));
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