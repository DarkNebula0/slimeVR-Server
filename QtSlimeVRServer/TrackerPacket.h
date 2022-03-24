#pragma once

#include "PacketBase.h"
#include "CharArray.h"

namespace Network
{
    namespace Packet {
        namespace TrackerPacket {
#pragma pack(push, 1)

            namespace Receive {
                enum EID : uint32_t {
                    Pairing = 0x00,
                    HeartBeat = 0x01,
                    Handshake = 0x02,
                    RSSI = 0x03,
                };

                struct SHeartBeat : SPacketHeader<SHeartBeat, EID::HeartBeat> {
                };

                struct SHandshake : SDefaultPacketHeader<SHandshake, EID::Handshake> {
                    uint32_t nImu;
                    CCharArray<6> achMac;
                };

                struct SRSSI : SDefaultPacketHeader<SHandshake, EID::RSSI> {
                    int8_t nRSSI;
                };
                
            }

            namespace Send {
                enum EID : uint32_t {
                    Pairing = 0x00,
                    HeartBeat = 0x01,
                    Handshake = 0x02,
                };

                struct SPairing : SPacketHeader<SPairing, EID::Pairing> {
                };

                struct SHandshake : SDefaultPacketHeader<SHandshake, EID::Handshake> {
                };

                struct SHeartBeat : SPacketHeader<SHeartBeat, EID::HeartBeat> {
                };
            }
#pragma pack(pop)
        }
    }

}