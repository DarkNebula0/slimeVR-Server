#pragma once

#include <QObject>
#include <QString>
#include <Qt3DCore>
#include <library/Singleton.h>


class CGui : public QObject, public CSingleton<CGui>
{
    friend class CSingleton<CGui>;
	Q_OBJECT
	Q_PROPERTY(QVector3D test READ test WRITE setTest NOTIFY testChanged)
    Q_PROPERTY(uint32_t nBridgeState READ bridgeState NOTIFY bridgeStateChanged)
private:
    CGui();
	 ~CGui();
public:
    QVector3D test() const {
        return m_oTestTransform;
    }

    uint32_t bridgeState() {
        return this->m_nBrdigeState;
    }
public:
    void updateBrdigeState();
    void setTest(const QVector3D& a) {
        if (a != m_oTestTransform) {
            m_oTestTransform = a;
            emit testChanged();
        }
    }
private:
    uint32_t m_nBrdigeState;
public:
	QVector3D m_oTestTransform;
signals:
    void testChanged();
    void bridgeStateChanged();
public slots:
	void pairTracker();
    void connectToBridge();
};

extern CGui* GuiInstance;