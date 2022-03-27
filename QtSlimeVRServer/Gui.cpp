#include "Gui.h"
#include <QDebug>
#include "BroadcastSend.h"
#include <library/Logger.h>
#include "../Core/Bridge.h"

CGui* GuiInstance = CGui::instance();


CGui::CGui()
	: QObject(nullptr), m_oTestTransform(0, 0, 0)
	, m_nBrdigeState(static_cast<uint32_t>(VRDriver::EBridgeState::Disconnected)) {

}

CGui::~CGui()
{}

// Callbacks
void CGui::pairTracker() {

	LOGI("Pairing new trackers");

	Broadcast::Packet::TrackerServer::SendPairing();
}

void CGui::connectToBridge()
{
	BridgeInstance->open();
	this->updateBrdigeState();
}


// Events
void CGui::updateBrdigeState()
{
	if (this->m_nBrdigeState == static_cast<uint32_t>(BridgeInstance->state())) {
		return;
	}

	this->m_nBrdigeState = static_cast<uint32_t>(BridgeInstance->state());
	return emit this->bridgeStateChanged();
}