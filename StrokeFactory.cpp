#include "stdafx.h"
#include "StrokeFactory.h"
#include "GlobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

StrokeFactory::StrokeFactory()
{
}


struct StrokeTag {};
typedef boost::singleton_pool<StrokeTag, sizeof(Stroke)> strokePool_;


StrokeFactory::~StrokeFactory()
{
	clear();
}

std::shared_ptr<StrokeFactory> StrokeFactory::instance_;
std::mutex StrokeFactory::mutex_;
//std::shared_ptr<boost::pool<>> StrokeFactory::strokePool_;
//std::mutex StrokeFactory::strokeMutex_;


StrokeFactory& StrokeFactory::instance()
{
	if (!instance_)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (!instance_)
			instance_ = std::make_shared<StrokeFactory>();
	}
	return *instance_;
}

Stroke* StrokeFactory::getStroke()
{
	auto p = static_cast<Stroke*>(strokePool_::malloc());
	queue_.push(p);
	return p;
}

void StrokeFactory::clear()
{
	Stroke* p = 0;
	while ((p = queue_.pop()))
		strokePool_::free(p);
}
