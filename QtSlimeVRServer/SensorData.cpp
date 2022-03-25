#include "SensorData.h"
#include "TrackerPacket.h"
#include "Tracker.h"
#include "InfoSend.h"
#include "Logger.h"
#include "Defines.h"

using namespace Network::Packet::TrackerPacket::Receive;

void SensorData::Packet::TrackerServer::RotationDataRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SRotationdata);
	const SRotationdata* p = reinterpret_cast<const SRotationdata*>(i_oPacket.buffer());

	printf_s("new rotation data %i %f %f %f %f \n", p->nId, p->dSensorRotation, p->dX, p->dY, p->dZ);
}