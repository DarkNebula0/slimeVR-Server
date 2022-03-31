#pragma once

#include <QTransform>
#include <qvector3d.h>
#include <qquaternion.h>


namespace VRProcessor {
	class CTransform
	{
	public:
		CTransform();
		virtual ~CTransform();
	public: 
		void combineWithParent(const CTransform& i_oTransform);
		void combineWithParentGlobalRotation(const CTransform& i_oTransform);
	public:
		void setRotation(const QQuaternion &i_oRot) {
			this->m_oRot = i_oRot;
		}
		void setTranslation(const QVector3D& i_oTranslation) {
			this->m_oTranslation = i_oTranslation;
		}
		void setScale(const QVector3D& i_oScale) {
			this->m_oScale = i_oScale;
		}
	public:
		__inline QQuaternion& rotation() {
			return this->m_oRot;
		}
		__inline QVector3D& translation() {
			return this->m_oTranslation;
		}
		__inline QVector3D& scale() {
			return this->m_oScale;
		}
	private:
		QQuaternion m_oRot;
		QVector3D m_oTranslation;
		QVector3D m_oScale;
	};
}
