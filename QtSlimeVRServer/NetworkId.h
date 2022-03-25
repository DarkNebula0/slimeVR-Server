#pragma once
#include <type_traits>
#include <atomic>
#include "Defines.h"
#include "BaseServer.h"
#include "../Core/MutexVector.h"
#include <QHostAddress>

namespace Network
{
	class IId
	{
	public:
		IId(const uint64_t i_nId = 0, const QHostAddress I_oIp = QHostAddress::LocalHost)
			: m_nId(i_nId)
		{
		}

	public:
		uint64_t networkId() const
		{
			return this->m_nId;
		}

		QHostAddress networkIp() const
		{
			return this->m_oIp;
		}

	public:
		void setID(const uint64_t i_nId)
		{
			this->m_nId = i_nId;
		}
		void setIP(const QHostAddress I_oIp) {
			this->m_oIp = I_oIp;
		}

	private:
		uint64_t m_nId;
		QHostAddress m_oIp;
	};

	template < typename TSession, typename std::enable_if< std::is_base_of< Network::IId, TSession >::value >::type* = nullptr >
	class IIdHandler
	{
	public:
		IIdHandler(CBaseServer< TSession >* i_pServer)
			: m_pServer(i_pServer), m_nLastId(1)
		{
		}

	public:
		std::shared_ptr< TSession > findNetworkId(const uint64_t i_nNetworkId)
		{
			auto& apSessions = this->m_pServer->sessions();

			MutexVectorLockGuard(apSessions);
			for (auto& pSession : apSessions)
			{
				if (pSession->networkId() == i_nNetworkId)
				{
					return pSession;
				}
			}

			return nullptr;
		}

		std::shared_ptr< TSession > findNetworkIp(const QHostAddress i_oNetworkIp)
		{
			auto& apSessions = this->m_pServer->sessions();

			MutexVectorLockGuard(apSessions);
			for (auto& pSession : apSessions)
			{
				if (pSession->networkIp() == i_oNetworkIp)
				{
					return pSession;
				}
			}

			return nullptr;
		}

	public:
		uint64_t newNetworkId()
		{
			return this->m_nLastId++;
		}

	private:
		CBaseServer< TSession >* m_pServer;
		std::atomic< uint64_t > m_nLastId;
	};
}
