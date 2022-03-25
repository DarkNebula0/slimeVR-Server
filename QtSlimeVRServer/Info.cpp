#include "Info.h"
#include "TrackerPacket.h"
#include "Tracker.h"
#include "InfoSend.h"
#include "Logger.h"
#include "Global.h"

using namespace Network::Packet::TrackerPacket::Receive;

void Info::Packet::TrackerServer::HandshakeRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SHandshake);
	const SHandshake *p = reinterpret_cast<const SHandshake*>(i_oPacket.buffer());

	// Set basic tracker info
	auto &trackerInfo = i_pSession->tracker().info();
	trackerInfo.eIMU0 = static_cast<CTracker::EImu>(p->nImu0);
	trackerInfo.eIMU1 = static_cast<CTracker::EImu>(p->nImu1);
	trackerInfo.chMAC =p->achMac;
	i_pSession->tracker().setReady();

	LOGI_DEBUG("[HandshakeRequest] New Tracker IMU0-Type: " + std::to_string(p->nImu0) + " IMU1 - Type: " + std::to_string(p->nImu1));

	SendHandshake(i_pSession);
}

void Info::Packet::TrackerServer::HeartBeatRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	i_pSession->restartHeartBeatTimer();
}

void Info::Packet::TrackerServer::RSSIRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SRSSI);
	const SRSSI *p = reinterpret_cast<const SRSSI*>(i_oPacket.buffer());
	i_pSession->tracker().setRSSI(p->nRSSI);

	LOGI_DEBUG("[RSSIRequest] New rssi value from tracker: " + i_pSession->networkIp().toString().toStdString() + " rssi: " + std::to_string(p->nRSSI));
}

void Info::Packet::TrackerServer::SensorStateRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SSensorState);
	const SSensorState *p = reinterpret_cast<const SSensorState*>(i_oPacket.buffer());

	// Update sensor state
	auto& trackerInfo = i_pSession->tracker().info();
	trackerInfo.eIMUState0 = static_cast<CTracker::EEmuState>(p->nSensor0State);
	trackerInfo.eIMUState1 = static_cast<CTracker::EEmuState>(p->nSensor1State);

	LOGI_DEBUG("[SensorStateRequest] New sensor state from tracker: " + i_pSession->networkIp().toString().toStdString() + " sensor0: " + std::to_string(p->nSensor0State) + " sensor1: " + std::to_string(p->nSensor1State));
}