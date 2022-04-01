#include "TransformNode.h"
#include <library/LockGuard.h>
#include "Exceptions.h"

VRProcessor::CTransformNode::CTransformNode(bool i_bLocalRotation)
	: m_pParent(nullptr), m_bLocalRotation(i_bLocalRotation)
{}

VRProcessor::CTransformNode::~CTransformNode()
{}

void VRProcessor::CTransformNode::updateWorldTransform()
{
	this->m_oWorldTransform = this->m_oLocalTransform;
	if (this->m_pParent) {
		if (this->m_bLocalRotation) {
			this->m_oWorldTransform.combineWithParent(this->m_pParent->m_oWorldTransform);
		}
		else {
			this->m_oWorldTransform.combineWithParentGlobalRotation(this->m_pParent->m_oWorldTransform);
		}
	}
}

void VRProcessor::CTransformNode::addChild(std::shared_ptr<CTransformNode> i_pChild)
{
	if (i_pChild->m_pParent) {
		throw CNodeParentAlreadySet();
	}

	i_pChild->m_pParent = this->shared_from_this();

	MutexVectorLockGuard(this->m_apChildren);
	this->m_apChildren.push_back(i_pChild);
}

void VRProcessor::CTransformNode::update()
{
	MutexVectorLockGuard(this->m_apChildren);
	for (auto pNode : this->m_apChildren) {
		pNode->update();
	}
}

