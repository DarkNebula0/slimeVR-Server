#include "Transform.h"

#include <qdebug.h>

VRProcessor::CTransform::CTransform(): m_oScale(1,1,1)
{
}

VRProcessor::CTransform::~CTransform()
{
}

void VRProcessor::CTransform::combineWithParent(const CTransform& i_oTransform)
{
	this->m_oScale *= i_oTransform.m_oScale;
	this->m_oRot *= i_oTransform.m_oRot;
	this->m_oTranslation *= i_oTransform.m_oScale;
}

void VRProcessor::CTransform::combineWithParentGlobalRotation(const CTransform& i_oTransform)
{

	this->m_oScale *= i_oTransform.m_oScale;
	this->m_oTranslation *= i_oTransform.m_oScale;
	
	if (!m_oTranslation.isNull())
	{
		qDebug() << i_oTransform.m_oRot;

		this->m_oRot = QQuaternion(((this->m_oRot * this->m_oTranslation) + i_oTransform.m_oTranslation).toVector4D());
	}
}