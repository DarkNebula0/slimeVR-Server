#include "Gui.h"
#include <QDebug>
#include "BroadcastSend.h"
#include "Logger.h"


CGui* GuiInstance = CGui::instance();


void CGui::buttonClicked() {

	LOGI("Pairing new trackers");
	//m_oTestTransform.setX(m_oTestTransform.x() + 10);
	//m_oTestTransform.setY(m_oTestTransform.y() + 10);
	//m_oTestTransform.setZ(m_oTestTransform.z() + 10);
	//emit testChanged();

	Broadcast::Packet::TrackerServer::SendPairing();
}

CGui::~CGui()
{
}

CGui::CGui() : QObject(nullptr), m_oTestTransform(0,0,0) {

}