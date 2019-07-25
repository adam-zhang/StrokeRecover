#include "stdafx.h"
#include "GlobalVariable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GlobalVariable::GlobalVariable()
	: messageWindow_(NULL)
{
}


GlobalVariable::~GlobalVariable()
{
	instance_.reset();
}

std::shared_ptr<GlobalVariable> GlobalVariable::instance_;
std::mutex GlobalVariable::m_;

GlobalVariable& GlobalVariable::instance()
{
	if (!instance_)
	{
		std::lock_guard<std::mutex> lock(m_);
		if (!instance_)
			instance_ = std::shared_ptr<GlobalVariable>(new GlobalVariable);
	}
	return *instance_;
}


//std::shared_ptr<Stroke> GlobalVariable::strokes(size_t value)
//{
//	if (strokes_.size() > value)
//		return strokes_[value];
//	return std::shared_ptr<Stroke>();
//}

//void GlobalVariable::pushStroke(Stroke* value)
//{
//	std::lock_guard<std::mutex> lock(m_);
//	queue_.push(value);
//}

//Stroke* GlobalVariable::popStroke()
//{
//	//std::lock_guard<std::mutex> lock(m_);
//	//assert(queue_.size() != 0);
//	auto p = queue_.pop();
//	return p;
//}

//bool GlobalVariable::strokesEmpty()
//{
//	//std::lock_guard<std::mutex> lock(m_);
//	return queue_.empty();
//}

//void GlobalVariable::clearStrokes()
//{
//	//std::lock_guard<std::mutex> lock(m_);
//	while (!queue_.empty())
//		queue_.pop();
//}
