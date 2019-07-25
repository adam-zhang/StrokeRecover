#pragma once
//#include <thread>
//#include <memory>
//#include <mutex>
//#include <condition_variable>
//#include <list>
//#include <vector>
//#include "Queue.h"
//
//class Gdiplus::Bitmap;
//struct Stroke;
//class Painter;
//
//class DrawingData
//{
//public:
//	DrawingData(CWnd*, std::shared_ptr<Painter>&);
//	~DrawingData();
//private:
//	CWnd* window_;
//	std::thread thread_;
//	std::shared_ptr<Gdiplus::Bitmap> bitmap_;
//	std::shared_ptr<Painter> painter_;
//	bool stop_;
//public:
//	std::shared_ptr<Painter>& painter()
//	{
//		return painter_;
//	}
//private:
//	void doPainting();
//	std::queue<std::shared_ptr<Stroke>> queue_;
//	std::vector<std::shared_ptr<Stroke>> savedStrokes_;
//	std::mutex mutex_;
//	std::condition_variable event_;
//public:
//	void push(const std::shared_ptr<Stroke>& value);
//	std::shared_ptr<Stroke> pop();
//	virtual void clear();
//	void redraw();
//protected:
//	virtual void draw();
//	void draw(const std::shared_ptr<Stroke>&);
//	std::vector<std::shared_ptr<Stroke>>& savedStrokes()
//	{
//		return savedStrokes_;
//	}
//};
//
//class DrawingSingleValue : public DrawingData
//{
//public:
//	DrawingSingleValue(CWnd*, std::shared_ptr<Painter>&);
//private:
//	size_t index_;
//public:
//	void increase();
//	void clear();
//	void draw();
//	void redraw();
//};
