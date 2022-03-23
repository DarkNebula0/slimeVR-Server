#pragma once
#include "Defines.h"
#include "MutexVector.h"
#include "NetworkPacket.h"

#include <QNetworkDatagram>
#include <QUdpSocket>
#include <memory>

namespace Network {
	template<typename TSession>
	class CBaseServer
	{
	public:
		CBaseServer();
		virtual ~CBaseServer();

	public:
		void initialize(QHostAddress i_oIp, ushort i_shPort);
	public:
		virtual void onSuccessfulListen() { }
	public:
		void addSession(const std::shared_ptr<TSession>& i_pSession)
		{
			this->m_apSessions.push_back(i_pSession);
		}

		void removeSession(const std::shared_ptr<TSession>& i_pSession)
		{
			this->m_apSessions.remove(i_pSession);
		}

		void broadcast(const char* i_pBuffer, size_t i_nSize);
	public:
		size_t connectionCount() const
		{
			return this->m_apSessions.size();
		}

		CMutexVector<std::shared_ptr<TSession>>& sessions()
		{
			return this->m_apSessions;
		}

		QUdpSocket* getSocket() {
			return &m_oSocket;
		}

	private:
		CMutexVector<std::shared_ptr<TSession>> m_apSessions;
		QUdpSocket m_oSocket;
	};


	template<typename TSession>
	CBaseServer<TSession>::CBaseServer()
	{ };

	template<typename TSession>
	CBaseServer<TSession>::~CBaseServer() = default;

	template<typename TSession>
	inline void CBaseServer<TSession>::initialize(QHostAddress i_oIp, ushort i_shPort)
	{
		this->m_oSocket.bind(i_oIp, i_shPort);
		this->onSuccessfulListen();
	}
	template<typename TSession>
	inline void CBaseServer<TSession>::broadcast(const char* i_pBuffer, size_t i_nSize)
	{
		this->m_oSocket.writeDatagram(i_pBuffer, i_nSize, QHostAddress::Broadcast, UDP_PORT);
	}
}
