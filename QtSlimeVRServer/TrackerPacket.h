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
                    RawCalibrationDate = 0x06,
                    CalibrationFinished = 0x07,
                    Config = 0x08,
                    PingPong = 0x0A,
                    BatteryLevel = 0x0C,
                    Tap = 0x0D,
                    Error = 0x0E,
                    SensorInfo = 0x0F,
                    RotationData = 0x11,
                    MagnetometerAccuracy = 0x12,
                    SignalStrength = 0x13,
                    Temperature = 0x14,
                    Inspection = 0x69
                };

                struct SHeartBeat : SPacketHeader<SHeartBeat, EID::HeartBeat> {
                };

                struct SHandshake : SDefaultPacketHeader<SHandshake, EID::Handshake> {
                    uint32_t nImu;
                    CCharArray<6> achMac;
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