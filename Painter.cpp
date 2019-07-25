#include "stdafx.h"
#include "Painter.h"
#include "GlobalData.h"
#include "GlobalVariable.h"
#include "Debugger.h"
#include "DrawingData.h"
#include <algorithm>
#include <gdiplus.h>
#include <cassert>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;


inline float distance(float x1, float y1, float x2, float y2)
{
	x2 -= x1;
	y2 -= y1;
	return sqrtf(x2*x2 + y2*y2);
}


inline bool equZero(const double a)
{
	return (fabs(a) < 1e-6 );
}

inline float lerp(float a, float b, float f)
{
	return a + f*(b - a);
}

void SmoothDraw(Gdiplus::Graphics& g, float x1, float y1, float x2, float y2, float p1, float p2)
{
	Gdiplus::SolidBrush brush(Gdiplus::Color(0, 0, 0));
	//Gdiplus::Pen pen(&br, 1.0f);
	//Debugger::write("SmoothDraw");
	float dist = distance(x1, y1, x2, y2);
	if (equZero(dist))
		return;
	float c = dist / 60.0f;
	float step = 1.0f;
	if (c > step)
		c = step;
	float t = 0.0f;
	float xt = x1, yt = y1, rt = p2;
	float b;

	int sum = 0;
	while (dist > t)
	{
		b = powf(t / dist, 3.0f);
		xt = lerp(x1, x2, b);
		yt = lerp(y1, y2, b);
		rt = lerp(p1, p2, b);
		//pen.SetWidth(rt);
		//Gdiplus::SolidBrush brush(Gdiplus::Color::Black);
		g.FillEllipse(&brush, xt, yt, rt, rt);
		t += c;
		++sum;
	}
}

static shared_ptr<Stroke> convertRatio(Stroke* data, UINT width)
{
	float ratio = static_cast<float>(width) / GlobalVariable::instance().initInfo()->maxX;
	shared_ptr<Stroke> stroke = make_shared<Stroke>(*data);
	stroke->x = stroke->x * ratio;
	stroke->y = stroke->y * ratio;
	return stroke;
}

void StartStroke(Gdiplus::Graphics& g, const shared_ptr<Stroke>& data)
{
	float bold = lerp(GlobalVariable::instance().initInfo()->min_pen_width, GlobalVariable::instance().initInfo()->max_pen_width, powf(data->pressure, 3.0));
	static float bold1 = GlobalVariable::instance().initInfo()->min_pen_width;
	static shared_ptr<Stroke> preStroke;

	if (preStroke)
	{
		bold1 = GlobalVariable::instance().initInfo()->min_pen_width;
		if (data->status != PEN_STATUS::PEN_DOWN)
			SmoothDraw(g, preStroke->x, preStroke->y, data->x, data->y, bold1, bold);
	}
	bold1 = bold;
	preStroke = data;
}



static void drawImage(HWND window, Gdiplus::Bitmap& bmp)
{
	auto graphics = shared_ptr<Gdiplus::Graphics>(Gdiplus::Graphics::FromHWND(window));
	auto hdc = graphics->GetHDC();
	auto memDC = CreateCompatibleDC(hdc);   
	HBITMAP bmpPtr = NULL;
	bmp.GetHBITMAP(Gdiplus::Color::White, &bmpPtr);
	SelectObject(memDC, bmpPtr);
	auto ret = BitBlt(hdc, 0, 0, bmp.GetWidth(), bmp.GetHeight(), memDC, 0, 0, SRCCOPY);
	assert(ret);
	DeleteDC(memDC);             
	DeleteObject(bmpPtr);          
	graphics->ReleaseHDC(hdc);
}

//static void d2dDrawImage(HWND window, Gdiplus::Bitmap& bmp)
//{
//	Gdiplus::Rect rect(0, 0, bmp.GetWidth(), bmp.GetHeight() );
//	Gdiplus::BitmapData pData;
//	bmp.LockBits(&rect, Gdiplus::ImageLockModeRead, bmp.GetPixelFormat(), &pData);
//}

void paintStroke(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke* stroke)
{
	auto data = convertRatio(stroke, bitmap->GetWidth());
	Gdiplus::Graphics g(bitmap.get());
	g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
	StartStroke(g, data);
	drawImage(window->GetSafeHwnd(), *bitmap);
}

void paintBlank(shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	shared_ptr<Gdiplus::SolidBrush> brush = make_shared<Gdiplus::SolidBrush>(Gdiplus::Color::White);
	Gdiplus::Graphics g(bitmap.get());
	Gdiplus::Rect rect(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
	g.FillRectangle(brush.get(), rect.X, rect.Y, rect.Width, rect.Height);
}

void clearStroke(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	paintBlank(bitmap);
	drawImage(window->GetSafeHwnd(), *bitmap);
}

void StrokesPainter::clear(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	clearStroke(window, bitmap);
}

void StrokesPainter::draw(CWnd* window, std::shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke* stroke)
{
	paintStroke(window, bitmap, stroke);
}


//static float getY(float width, float strokeX)
//{
//	return 0;
//}
//
//static float getX(float width, size_t index)
//{
//
//}

static void drawX(shared_ptr<Gdiplus::Bitmap>& bitmap, float x1, float y1, float x2, float y2)
{
	Gdiplus::Graphics g(bitmap.get());
	Gdiplus::Pen pen(Gdiplus::Color::Black);
	Debugger::write("x1", x1, "y1", y1, "x2", x2, "y2", y2);
	g.DrawLine(&pen, x1, y1, x2, y2);
}

//float calculateX(float width, float value)
//{
//	const float points = 500;
//	return points / width * value;
//}

float StrokesXPainter::calculateY(float max, float value)
{
	return value / max;
}

void demoDraw(shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	Gdiplus::Graphics g(bitmap.get());
	Gdiplus::Pen pen(Gdiplus::Color::Black);
	g.DrawLine(&pen, 0, 0, bitmap->GetWidth(), bitmap->GetHeight());
}

void StrokesXPainter::draw(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke* stroke)
{
	static Stroke* previous;
	if (!previous)
	{
		previous = stroke;
		return;
	}
	auto x1 = calculateX(static_cast<float>(bitmap->GetWidth()), static_cast<float>(index() - 1));
	auto y1 = calculateY(static_cast<float>(GlobalVariable::instance().initInfo()->maxX), static_cast<float>(previous->x * bitmap->GetHeight()));
	auto x2 = calculateX(static_cast<float>(bitmap->GetWidth()), static_cast<float>(index()));
	auto y2 = calculateY(static_cast<float>(GlobalVariable::instance().initInfo()->maxX ), stroke->x * bitmap->GetHeight());
	if (x1 > bitmap->GetWidth())
	{
		redraw(window, bitmap);
		x1 = calculateX(static_cast<float>(bitmap->GetWidth()), static_cast<float>(index() - 1));
		x2 = calculateX(static_cast<float>(bitmap->GetWidth()), static_cast<float>(index() - 1));
	}
	drawX(bitmap, x1, y1, x2, y2);
	drawImage(window->GetSafeHwnd(), *bitmap);
	previous = stroke;
	setIndex(index() + 1);
}

void StrokesXPainter::redraw(CWnd* painter, shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	//vector<float> 
	//for_each(storedValues().begin(), storedValues().end() [] (Stroke* p)
	//{

	//});
}
//

//

float StrokesXPainter::calculateX(float width, float value)
{
	auto w = width / ratio();
	return value / ratio();
}



void StrokesXPainter::clear(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap)
{
	clearStroke(window, bitmap);
	SingleValuePainter::clean();
}

//void StrokesYPainter::draw(shared_ptr<Gdiplus::Bitmap>& bitmap, const shared_ptr<Stroke>& stroke)
//{
//	//float x = calculateX(bitmap->GetWidth(), index());
//	//float y = calculateY(GlobalVariable::instance().initInfo()->maxX, stroke->y);
//}

//void StrokesYPainter::clear(shared_ptr<Gdiplus::Bitmap>& bitmap)
//{
//	paintBlank(bitmap);
//}

//void StrokesPressurePainter::draw(shared_ptr<Gdiplus::Bitmap>& bitmap, const shared_ptr<Stroke>& stroke)
//{
//
//}

//void StrokesPressurePainter::clear(shared_ptr<Gdiplus::Bitmap>& bitmap)
//{
//	paintBlank(bitmap);
//}


//void SingleValuePainter::redraw(CWnd* window, shared_ptr<Gdiplus::Bitmap>& bitmap)
//{
//	//assert(parent_);
//	clear(window, bitmap);
//	shrink();
//	for(auto p : storedValues())
//		
//}
