#include "SideTasksController.h"
#include "SideTasks.h"

#include <QThread>

CSideTasksController* SideTaskControllerInstance = CSideTasksController::instance();

CSideTasksController::CSideTasksController()
	: QObject(nullptr), m_pWorkerThread(new QThread(this)), m_pSideTasksWorker(new CSideTasks())
{}

CSideTasksController::~CSideTasksController()
{
	this->m_pWorkerThread->quit();
	this->m_pWorkerThread->wait();
	delete this->m_pWorkerThread;
	delete this->m_pSideTasksWorker;
}

void CSideTasksController::start()
{
	if (this->m_pWorkerThread->isRunning()) {
		return;
	}

	// Start worker thread
	this->m_pSideTasksWorker->moveToThread(this->m_pWorkerThread);
	connect(this, &CSideTasksController::operate, this->m_pSideTasksWorker, &CSideTasks::operate);
	this->m_pWorkerThread->start();
	emit this->operate();
}

void CSideTasksController::stop()
{
	this->m_pSideTasksWorker->stopRequest();
}
