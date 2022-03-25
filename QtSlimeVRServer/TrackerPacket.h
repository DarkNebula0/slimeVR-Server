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
                    SensorState= 0x04,
                    RotationData = 0x05,
                };

                struct SHeartBeat : SPacketHeader<SHeartBeat, EID::HeartBeat> {
                };

                struct SHandshake : SDefaultPacketHeader<SHandshake, EID::Handshake> {
                    uint32_t nImu0;
                    uint32_t nImu1;
                    CCharArray<6> achMac;
                };

                struct SRSSI : SDefaultPacketHeader<SRSSI, EID::RSSI> {
                    int8_t nRSSI;
                };

                struct SSensorState : SDefaultPacketHeader<SSensorState, EID::SensorState> {
                    uint8_t nSensor0State;
                    uint8_t nSensor1State;
                };

                struct SRotationdata : SDefaultPacketHeader<SRotationdata, EID::RotationData> {
                    uint8_t nId;
                    double dSensorRotation;
                    double dX;
                    double dY;
                    double dZ;
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