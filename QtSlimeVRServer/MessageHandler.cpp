#include "MessageHandler.h"
#include "../Core/Bridge.h"
#include "../Core/BridgeHandler.h"
#include "../Core/ProtobufMessages.pb.h"

VRDriver::CMessageHandler* MessageHandlerInstance = VRDriver::CMessageHandler::instance();

VRDriver::CMessageHandler::CMessageHandler() : m_pMessage(new messages::ProtobufMessage())
{}

VRDriver::CMessageHandler::~CMessageHandler()
{
	delete this->m_pMessage;
}

void VRDriver::CMessageHandler::initialize()
{
	BridgeMessageHandlerInstance->createPool(1);
	// Register msg handlers
}

void VRDriver::CMessageHandler::handleTasks()
{
	// Check bridge state and handle update
	if (BridgeInstance->state() != EBridgeState::Connected) {
		return;
	}

	while (BridgeInstance->getNextMessage(this->m_pMessage))
	{
		// Add to thread queue
		BridgeMessageHandlerInstance->addTask(*this->m_pMessage);
	}
}