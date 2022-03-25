#pragma once

#include <cstdint>
#include <cstring>
#include <functional>

namespace Network
{
    namespace Packet {
#pragma pack(push, 1)

        template<typename TPacket = uint8_t, uint32_t TID = 0>
        struct SPacketHeader {
        private:
            uint16_t shLength = sizeof(TPacket);
            uint8_t chVerifier = 0xF0;
            uint32_t nID = TID;
        public:
            [[nodiscard]] uint32_t id() const { return this->nID; }

            [[nodiscard]] constexpr uint16_t length() const { return this->shLength; }

            [[nodiscard]] uint8_t verifier() const { return this->chVerifier; }

        public:
            explicit SPacketHeader(const bool i_bClear = true) {
                if (i_bClear) {
                    std::memset(reinterpret_cast<char*>(this) + sizeof(SPacketHeader), 0,
                        sizeof(TPacket) - sizeof(SPacketHeader));
                }
            };
        };

#pragma pack(pop)

    }
}

template<typename TPacket = uint8_t, uint32_t TID = 0>
using SDefaultPacketHeader = Network::Packet::SPacketHeader<TPacket, TID>;