#include "stdafx.h"
#include "PaintingData.h"
#include "GlobalData.h"
#include "Performence.h"
#include "Painter.h"
#include <thread>
#include <sstream>
#include <gdiplus.h>
#include <cassert>

using namespace std;

std::shared_ptr<Gdiplus::Bitmap> createBitmap(CWnd* window)
{
	CRect rect;
	window->GetClientRect(rect);
	auto bitmap = make_shared<Gdiplus::Bitmap>(rect.Width(), rect.Height());
	return bitmap;
}

PaintingData::PaintingData(CWnd* window, std::shared_ptr<Painter>& painter)
	: window_(window)
	, painter_(painter)
	//, stop_(false)
{
	bitmap_ = createBitmap(window_);
	//thread_ = thread(&PaintingData::doPaint, this);
}


PaintingData::~PaintingData()
{
	//stop();
	//thread_.join();
}

//Stroke* PaintingData::pop()
//{
//	unique_lock<mutex> lock(mutex_);
//	assert(!queue_.empty());
//	auto p = queue_.pop();
//	return p;
//}

//void PaintingData::push(Stroke* value)
//{
//	unique_lock<mutex> lock(mutex_);
//	queue_.push(value);
//}

//void output(const shared_ptr<Stroke>& value)
//{
//	stringstream ss;
//	ss << "data:\n"
//		<< "x:" << value->x
//		<< " y:" << value->y
//		<< " pressure:" << value->pressure
//		<< endl;
//	OutputDebugStringA(ss.str().c_str());
//}

//void PaintingData::doPaint()
//{
//	//Debugger::write("doPaint", stop_);
//	//while(!stop_)
//	//{
//	//	if (queue_.empty())
//	//	{
//	//		this_thread::sleep_for(chrono::microseconds(10));
//	//		continue;
//	//	}
//		auto p = pop();
//		drawingFunc_(window_, bitmap_, p);
//	//}
//}

void PaintingData::clear()
{
	//assert(clearFunc_);
	//clearFunc_(window_, bitmap_);
	assert(painter_);
	painter_->clear(window_,  bitmap_);
}

void PaintingData::draw(Stroke* p)
{
	assert(painter_);
	painter_->draw(window_, bitmap_, p);
}

//void PaintingData::stop()
//{
//	//stop_ = true;
//	//if (thread_.joinable())
//	//	thread_.join();
//}
