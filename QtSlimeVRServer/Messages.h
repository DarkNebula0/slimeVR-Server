#pragma once

namespace messages {
	class ProtobufMessage;
}

namespace VRDriver {
	namespace Messages
	{
		void Position(const messages::ProtobufMessage* i_pMessage);
		void UserAction(const messages::ProtobufMessage* i_pMessage);
		void TrackerAdded(const messages::ProtobufMessage* i_pMessage);
		void TrackerStatus(const messages::ProtobufMessage* i_pMessage);
	};
}
