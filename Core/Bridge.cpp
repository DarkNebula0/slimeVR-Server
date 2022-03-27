#include "Bridge.h"

VRDriver::CBridge* BridgeInstance = VRDriver::CBridge::instance();

VRDriver::CBridge::CBridge() : m_pPipeHandle(INVALID_HANDLE_VALUE), m_eState(EBridgeState::Disconnected) {}

VRDriver::EBridgeState VRDriver::CBridge::open()
{
    if (m_pPipeHandle != INVALID_HANDLE_VALUE) {
        return EBridgeState::Connected;
    }

    this->m_pPipeHandle = CreateFileA("\\\\.\\pipe\\SlimeVRInput", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    this->m_eState = this->m_pPipeHandle != INVALID_HANDLE_VALUE ? EBridgeState::Connected : EBridgeState::Error;
    return this->m_eState;
}

void VRDriver::CBridge::initialize()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

VRDriver::EBridgeState VRDriver::CBridge::reset()
{
    this->close();
    return this->open();
}

VRDriver::EBridgeState VRDriver::CBridge::close()
{
    if (this->m_pPipeHandle) {
        CloseHandle(this->m_pPipeHandle);
    }

    this->m_eState = EBridgeState::Disconnected;
    return EBridgeState::Disconnected;
}

bool VRDriver::CBridge::getNextMessage(messages::ProtobufMessage* i_pMsg)
{
    if (this->m_pPipeHandle != INVALID_HANDLE_VALUE ) {
 
        DWORD nBytesRead = 0;
        uint32_t nSize = 0;
        bool newData = false;

        if (PeekNamedPipe(this->m_pPipeHandle, &nSize, 4, &nBytesRead, nullptr, nullptr) && i_pMsg) {
            char* pBuffer = new char[nSize];

            if (ReadFile(this->m_pPipeHandle, pBuffer, nSize, &nBytesRead, nullptr)) {
                newData = i_pMsg->ParseFromArray(pBuffer + 4, nSize - 4);
            }

            delete[] pBuffer;
        }
        return newData;
    }

    this->m_eState = EBridgeState::Error;
    return false;
}

bool VRDriver::CBridge::sendMessage(messages::ProtobufMessage* i_pMsg)
{
    DWORD nSend = 0;

    if (this->m_pPipeHandle != INVALID_HANDLE_VALUE) {
        if (i_pMsg) {
            uint32_t nSize = i_pMsg->ByteSizeLong() + 4;

            char* pBuffer = new char[nSize];
            
            // Set size
            *reinterpret_cast<uint32_t*>(pBuffer) = nSize;

            if (i_pMsg->SerializeToArray(pBuffer + 4, i_pMsg->ByteSizeLong())) {
               
                if (!WriteFile(this->m_pPipeHandle, pBuffer, nSize, &nSend, nullptr)) {
                    this->m_eState = EBridgeState::Error;
                }
            }

            delete[] pBuffer;
        }
    }
    else {
        this->m_eState = EBridgeState::Error;
    }

    return nSend > 0;
}