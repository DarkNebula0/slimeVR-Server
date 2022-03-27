#pragma once

#include <library/Singleton.h>
#include <QObject>

class QThread;
class CSideTasks;
class CSideTasksController : public QObject, public CSingleton<CSideTasksController>
{
	friend class CSingleton<CSideTasksController>;
	Q_OBJECT
private:
	CSideTasksController();
	~CSideTasksController();
private:
	QThread *m_pWorkerThread;
	CSideTasks* m_pSideTasksWorker;
private:
signals:
	void operate();
public:
	void start();
	void stop();
};

extern CSideTasksController* SideTaskControllerInstance;