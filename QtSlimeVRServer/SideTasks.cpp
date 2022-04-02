#include "SideTasks.h"
#include "Defines.h"
#include <library/Logger.h>
#include <QThread>
#include "TrackerServer.h"
#include "MessageHandler.h"
#include "../Core/HumanPoseProcessor.h"

CSideTasks::CSideTasks()
	:  m_bHasStopRequest(false)
{
}

CSideTasks::~CSideTasks()
{}

void CSideTasks::operate()
{
	while (!m_bHasStopRequest)
	{
		// Check for disconnected trackers and send heartbeat
		TrackerServerInstance->checkDisconnectedClients();

		// Remove disconnected clients
		TrackerServerInstance->handleDisconnectedClients();

		// Cehck for new msg from OpenVR bridge
		MessageHandlerInstance->handleTasks();

		// TODO: extract to own thread
		HumanPoseProcessorInstance->updatePose();

		QThread::msleep(SIDE_TASK_THREAD_DELAY_MS);
	}
}
