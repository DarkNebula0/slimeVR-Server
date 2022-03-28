#pragma once
#include <library/Singleton.h>

namespace messages {
	class ProtobufMessage;
}

namespace VRDriver {

class CMessageHandler:public CSingleton<CMessageHandler>
{
	friend CSingleton<CMessageHandler>;
private:
	CMessageHandler();
	virtual ~CMessageHandler();
private:
	messages::ProtobufMessage* m_pMessage;
public:
	void initialize();
	void handleTasks();
};

}


extern VRDriver::CMessageHandler* MessageHandlerInstance;