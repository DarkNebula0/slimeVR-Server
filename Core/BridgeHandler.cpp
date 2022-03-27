#include "BridgeHandler.h"
#include <library/ThreadPool.h>
#include <library/Logger.h>
#include <library/Global.h>

VRDriver::CBridgeHandler* BridgeMessageHandlerInstance = VRDriver::CBridgeHandler::instance();

VRDriver::CBridgeHandler::CBridgeHandler(): m_pPool(nullptr)
{}


VRDriver::CBridgeHandler::~CBridgeHandler()
{
	if (this->m_pPool)
	{
		delete this->m_pPool;
	}
}

void VRDriver::CBridgeHandler::createPool(const size_t i_nWorkerCount)
{
	if (!this->m_pPool)
	{
		this->m_pPool = new CThreadPool(i_nWorkerCount);
		this->m_pPool->execute();
	}
}

void VRDriver::CBridgeHandler::closePool()
{
	if (this->m_pPool)
	{
		this->m_pPool->stop(true);
	}
}

void VRDriver::CBridgeHandler::addTask(const messages::ProtobufMessage& i_oMessage)
{
	if (this->m_pPool)
	{
		this->m_pPool->addTask(std::bind(&CBridgeHandler::handle, this, std::move(i_oMessage)));
	}
}

void VRDriver::CBridgeHandler::handle(const messages::ProtobufMessage& i_oMessage)
{
	uint32_t nMsgId = i_oMessage.message_case();

	const auto& fnFunction = this->m_afnPacket[nMsgId];
	if (fnFunction)
	{
		fnFunction(messages::ProtobufMessage(i_oMessage));
	}
	else
	{
		LOGW_DEBUG("MessageHandler-Function [ CBridgeHandler ] Handler not found! ID: " + Utils::ToHexString<uint32_t>(nMsgId));
	}

}