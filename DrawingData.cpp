#include "stdafx.h"
//#include "DrawingData.h"
//#include "Painter.h"
//#include "GlobalData.h"
//#include <gdiplus.h>
//#include <sstream>
//#include <algorithm>
//#include "Performence.h"
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//using namespace std;
//
//DrawingData::DrawingData(CWnd* window, shared_ptr<Painter>& painter)
//	: window_(window)
//	, painter_(painter)
//	, stop_(false)
//{
//	assert(window);
//	assert(window->m_hWnd);
//	CRect rect;
//	window->GetClientRect(&rect);
//	thread_ = std::thread(&DrawingData::doPainting, this);
//	bitmap_ = make_shared<Gdiplus::Bitmap>(rect.Width(), rect.Height());
//}
//
//
//DrawingData::~DrawingData()
//{
//	thread_.detach();
//}
//
//
//void drawImage(HWND window, Gdiplus::Bitmap& bmp)
//{
//	//Performence p(TEXT("drawImage"));
//	auto graphics = shared_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromHWND(window));
//	auto hdc = graphics->GetHDC();
//	auto memDC = CreateCompatibleDC(hdc);   
//	HBITMAP bmpPtr = NULL;
//	bmp.GetHBITMAP(Gdiplus::Color::White, &bmpPtr);
//	SelectObject(memDC, bmpPtr);
//	auto ret = BitBlt(hdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), memDC, 0, 0, SRCCOPY);
//	assert(ret);
//	DeleteDC(memDC);             
//	DeleteObject(bmpPtr);          
//}
//
//void DrawingData::doPainting()
//{
//	CRect rect;
//	window_->GetClientRect(&rect);
//	while (!stop_)
//	{
//		draw();
//	}
//}
//
//void DrawingData::draw()
//{
//	auto stroke = pop();
//	if (!stroke)
//		return;
//	draw(stroke);
//	savedStrokes_.push_back(stroke);
//}
//
//void DrawingData::draw(const std::shared_ptr<Stroke>& stroke)
//{
//	painter_->draw(bitmap_, stroke);
//	drawImage(window_->m_hWnd, *bitmap_);
//}
//
//void DrawingSingleValue::redraw()
//{
//	clear();
//	for_each(savedStrokes().begin(), savedStrokes().end(), [this](const shared_ptr<Stroke>& stroke)
//	{
//		DrawingData::draw(stroke);
//	});
//}
//
//void DrawingSingleValue::draw()
//{
//	auto p = static_pointer_cast<SingleValuePainter>(painter());
//	p->setIndex(index_);
//	DrawingData::draw();
//	increase();
//}
//
//void DrawingData::push(const shared_ptr<Stroke>& value)
//{
//	if (!this)
//		return;
//	queue_.push(value);
//	event_.notify_one();
//}
//
//shared_ptr<Stroke> DrawingData::pop()
//{
//	std::unique_lock<std::mutex> lock(mutex_);
//	if (queue_.empty() == 0)
//		event_.wait(lock);
//	if (queue_.empty())
//		return shared_ptr<Stroke>();
//	auto p = queue_.front();
//	queue_.pop();
//	return p;
//}
//
//void DrawingData::clear()
//{
//	if (!painter_)
//		return;
//	painter_->clear(bitmap_);
//	drawImage(window_->m_hWnd, *bitmap_);
//}
//
//void DrawingSingleValue::clear()
//{
//	DrawingData::clear();
//	index_ = 0;
//}
//
//void DrawingSingleValue::increase()
//{
//	++index_;
//}
//
//DrawingSingleValue::DrawingSingleValue(CWnd* window, shared_ptr<Painter>& painter)
//	: DrawingData(window, painter)
//	, index_(0)
//{
//}

