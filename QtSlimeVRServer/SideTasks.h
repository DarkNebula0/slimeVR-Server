#pragma once

#include <QObject>

class CSideTasks : public QObject
{
	Q_OBJECT

public:
	CSideTasks();
	~CSideTasks();
private:
	bool m_bHasStopRequest;
public:
	void operate();
	_inline void stopRequest() {
		this->m_bHasStopRequest = true;
	}
};