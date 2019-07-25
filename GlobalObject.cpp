#include "stdafx.h"
#include "GlobalObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GlobalObject::GlobalObject()
{
	//event_ = CreateEvent(NULL, TRUE, FALSE, NULL);
}


GlobalObject::~GlobalObject()
{
	//if (event_)
	//{
	//	CloseHandle(event_);
	//	event_;
	//}
}

std::shared_ptr<GlobalObject> GlobalObject::instance_;

std::mutex GlobalObject::mutex_;
