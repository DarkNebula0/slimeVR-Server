#include "Gui.h"
#include <QDebug>
#include "BroadcastSend.h"
#include "Logger.h"

void CGui::buttonClicked() {

	LOGI("Pairing new trackers");
	Broadcast::Packet::TrackerServer::SendPairing();
}