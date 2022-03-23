#include "Broadcast.h"

// Brodcast events come only from the server itself and do not need to be edited 

void Broadcast::Packet::TrackerServer::PairingRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{}
