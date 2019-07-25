#pragma once
#include <queue>
#include <mutex>

//template<typename T>
//class Queue
//{
//public:
//	Queue() {};
//	~Queue() {};
//private:
//	std::queue<T> queue_;
//	std::mutex mutex_;
//public:
//
//	void push(const T& value)
//	{
//		std::lock_guard<std::mutex> lock(mutex_);
//		queue_.push(value);
//	}
//
//	T pop()
//	{
//		std::lock_guard<std::mutex> lock(mutex_);
//		auto value = queue_.front();
//		queue_.pop();
//		return value;
//	}
//
//	bool empty()
//	{
//		std::lock_guard<std::mutex> lock(mutex_);
//		return queue_.empty();
//	}
//
//	void clear()
//	{
//		std::lock_guard<std::mutex> lock(mutex_);
//		while (!queue_.empty())
//			queue_.pop();
//	}
//};

