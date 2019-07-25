#pragma once
#include <queue>
#include <memory>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <thread>
#include <atomic>
#include "ThreadSafeQueue.h"
//#include "Queue.h"

class Stroke;
class Gdiplus::Bitmap;
class Painter;

class PaintingData
{
private:
	PaintingData(const PaintingData&)=delete;
public:
	explicit PaintingData(CWnd*, std::shared_ptr<Painter>&);
	~PaintingData();
private:
	std::shared_ptr<Painter> painter_;
	//ThreadSafeQueue<Stroke*> queue_;
	//std::mutex mutex_;
	//std::condition_variable condition_;
	//std::function<void(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&, Stroke*)> drawingFunc_;
	//std::function<void(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&)> clearFunc_;
	CWnd* window_;
	std::shared_ptr<Gdiplus::Bitmap> bitmap_;
	std::thread thread_;
	//std::atomic<bool> stop_;
public:
	//void setDrawingFunc(std::function<void(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&,Stroke*)>& value)
	//{
	//	drawingFunc_ = value;
	//}
	//void setClearFunc(std::function<void(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&)> value)
	//{
	//	clearFunc_ = value;
	//}

	//void push(Stroke* value);
	void clear();
	//void stop();
	void draw(Stroke*);
private:
	Stroke* pop();
private:
	void doPaint();
};

