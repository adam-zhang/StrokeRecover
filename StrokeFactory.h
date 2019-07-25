#pragma once
#include <memory>
#include <mutex>
#include <boost/pool/pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <vector>
#include "ThreadSafeQueue.h"
//#include "GlobalData.h"

class Stroke;


class StrokeFactory
{
public:
	StrokeFactory();
	~StrokeFactory();
private:
	static std::shared_ptr<StrokeFactory> instance_;
	static std::mutex mutex_;
public:
	static StrokeFactory& instance();
public:
	Stroke* getStroke();
	void clear();
private:
	//std::shared_ptr<boost::pool<>> strokePool_;
	std::mutex strokeMutex_;
	ThreadSafeQueue<Stroke*> queue_;

};

