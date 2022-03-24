#pragma once

#include <QObject>
#include <QString>

class CGui : public QObject
{
	Q_OBJECT

public:
	 explicit CGui(QObject *i_pParent = 0): QObject(i_pParent) {};
	 virtual ~CGui() = default;
public slots:
	void buttonClicked();
};
