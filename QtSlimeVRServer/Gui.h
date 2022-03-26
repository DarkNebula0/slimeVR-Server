#pragma once

#include <QObject>
#include <QString>
#include <Qt3DCore>
#include "../Core/Singleton.h"

class CGui : public QObject, public CSingleton<CGui>
{
    friend class CSingleton<CGui>;
	Q_OBJECT
	Q_PROPERTY(QVector3D test READ test WRITE setTest NOTIFY testChanged)
private:
    CGui();
	 ~CGui();
public:
    void setTest(const QVector3D& a) {
        if (a != m_oTestTransform) {
            m_oTestTransform = a;
            emit testChanged();
        }
    }
    QVector3D test() const {
        return m_oTestTransform;
    }
signals:
    void testChanged();
public:
	QVector3D m_oTestTransform;
public slots:
	void buttonClicked();
};

extern CGui* GuiInstance;