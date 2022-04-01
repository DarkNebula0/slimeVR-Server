#include "SensorData.h"
#include "../Core/HumanPoseProcessor.h"
#include "TrackerPacket.h"
#include "InfoSend.h"
#include "Tracker.h"
#include "Defines.h"
#include "Gui.h"
#include <library/Logger.h>
#include <QQuaternion>
#include <iostream>
#include <math.h>

using namespace Network::Packet::TrackerPacket::Receive;

QQuaternion oTest = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), -(M_1_PI * 0.5F));

void SensorData::Packet::TrackerServer::RotationDataRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SRotationdata);
	const SRotationdata* p = reinterpret_cast<const SRotationdata*>(i_oPacket.buffer());
	
	// I dont have any fucking clue 

	QQuaternion oQuat = oTest * QQuaternion(QVector4D(p->dX, p->dY, p->dZ, p->dW));
	QVector3D qVec = oQuat.toEulerAngles();
	

	GuiInstance->m_oTestTransform.setX(qVec.x());
	GuiInstance->m_oTestTransform.setY(qVec.y());
	GuiInstance->m_oTestTransform.setZ(qVec.z());
	emit GuiInstance->testChanged();
}
