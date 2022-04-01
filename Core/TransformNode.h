#pragma once

#include "Transform.h"
#include <qvector.h>
#include <memory>
#include <library/MutexVector.h>

namespace VRProcessor {
	class CTransformNode: public std::enable_shared_from_this<CTransformNode>
	{
	public:
		CTransformNode(bool i_bLocalRotation);
		CTransformNode() : CTransformNode(false) {};
		~CTransformNode();
	private:
		void updateWorldTransform();
	public:
		void addChild(std::shared_ptr<CTransformNode> i_pChild);
		void update();
	public:
		__inline std::shared_ptr<CTransformNode> parent() {
			return this->m_pParent;
		}
		__inline CTransform* localTransform() {
			return &this->m_oLocalTransform;
		}
		__inline CTransform* worldTransform() {
			return &this->m_oWorldTransform;
		}
	public:
		static std::shared_ptr<CTransformNode> createInstance() {
			return std::make_shared<CTransformNode>();
		}
	private:
		std::shared_ptr<CTransformNode> m_pParent;
		CTransform m_oLocalTransform;
		CTransform m_oWorldTransform;
		CMutexVector<std::shared_ptr<CTransformNode>> m_apChildren;
		bool m_bLocalRotation;
	};
}