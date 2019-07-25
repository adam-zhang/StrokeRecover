#pragma once
#include <mutex>
#include <memory>
#include <condition_variable>

class GlobalObject
{
private:
	GlobalObject();
public:
	~GlobalObject();
public:
private:
	static std::shared_ptr<GlobalObject> instance_;
	static std::mutex mutex_;
public:
	static GlobalObject& instance()
	{
		if (!instance_)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			if (!instance_)
				instance_ = std::shared_ptr<GlobalObject>(new GlobalObject);
		}
		return *instance_;
	}
private:
	std::condition_variable event_;
public:
	void wait()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		event_.wait(lock);
	}
	void notify_all()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		event_.notify_all();
	}
	//HANDLE event_;
public:
	//HANDLE globalEvent()
	//{
	//	return event_;
	//}
	//bool resetEvent()
	//{
	//	return ResetEvent(event_) == TRUE;
	//}
	//bool setEvent()
	//{
	//	return SetEvent(event_) == TRUE;
	//}

	//bool pulseEvent()
	//{
	//	return PulseEvent(event_) == TRUE;
	//}

	//void wait()
	//{
	//	WaitForSingleObject(event_, INFINITE);
	//}
};

