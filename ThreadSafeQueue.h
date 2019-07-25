#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
//#include "Performence.h"

template<class T>
class ThreadSafeQueue
{
public:
	ThreadSafeQueue() {};
	~ThreadSafeQueue() {};
private:
	std::queue<T> queue_;
	std::mutex mutex_;
	std::condition_variable conditionVariable_;
public:
	T pop()
	{
		std::unique_lock<std::mutex> lock(mutex_);
		if (queue_.empty())
			conditionVariable_.wait(lock);
		T value = queue_.front();
		queue_.pop();
		return value;
	}
	void push(const T& value)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push(value);
		conditionVariable_.notify_one();
	}
	size_t size()
	{
		return queue_.size();
	}
	bool empty()
	{
		return queue_.empty();
	}

};



