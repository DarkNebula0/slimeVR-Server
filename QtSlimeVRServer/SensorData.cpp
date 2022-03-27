#include "SensorData.h"
#include "TrackerPacket.h"
#include "Tracker.h"
#include "InfoSend.h"
#include <library/Logger.h>
#include "Defines.h"
#include "Gui.h"
#include <iostream>
#include <QQuaternion>

using namespace Network::Packet::TrackerPacket::Receive;

void SensorData::Packet::TrackerServer::RotationDataRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SRotationdata);
	const SRotationdata* p = reinterpret_cast<const SRotationdata*>(i_oPacket.buffer());
	
	// I dont have any fucking clue 


	QQuaternion oQuat(QVector4D(p->dX, p->dY, p->dZ, p->dW));
	QVector3D qVec = oQuat.toEulerAngles();
	
	printf_s("new rotation data SensorID: %i Accuracy: %i Sensor Rotation: %f X: %f Y: %f Z: %f W: %f\n", p->nId, p->nAccuracy, p->dSensorRotation, p->dX, p->dY, p->dZ, p->dW);
	
	GuiInstance->m_oTestTransform.setX(qVec.x());
	GuiInstance->m_oTestTransform.setY(qVec.y());
	GuiInstance->m_oTestTransform.setZ(qVec.z());
	emit GuiInstance->testChanged();

}
