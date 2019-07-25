#include "stdafx.h"
#include "StrokesWindow.h"
//#include "Painter.h"
//#include "GlobalData.h"
//#include "Debugger.h"
//
//
//StrokesWindow::StrokesWindow()
//{
//}
//
//
//StrokesWindow::~StrokesWindow()
//{
//}
//
//
////void SmoothDraw(Gdiplus::Graphics& g, float x1, float y1, float x2, float y2, float p1, float p2)
////{
////	Gdiplus::SolidBrush br(Gdiplus::Color(0, 0, 0));
////	Gdiplus::Pen pen(&br, 1.0f);
////	//Debugger::write("SmoothDraw");
////	float dist = distance(x1, y1, x2, y2);
////	if (equZero(dist))
////		return;
////	float c = dist / 30.0f;
////	float step = 1.0f;
////	if (c > step)
////		c = step;
////	float t = 0.0f;
////	float xt = x1, yt = y1, rt = p2;
////	float b;
////
////	int sum = 0;
////	while (dist > t)
////	{
////		b = powf(t / dist, 3.0f);
////		xt = lerp(x1, x2, b);
////		yt = lerp(y1, y2, b);
////		rt = lerp(p1, p2, b);
////		pen.SetWidth(rt);
////		g.DrawEllipse(&pen, xt, yt, 2.0f*rt, 2.0f*rt);
////		t += c;
////		++sum;
////	}
////}
//
//static float distance(float x1, float y1, float x2, float y2)
//{
//	x2 -= x1;
//	y2 -= y1;
//	return sqrtf(x2*x2 + y2*y2);
//}
//
//bool equalZero(float value)
//{
//	return (fabs(value) < 1e-6 );
//}
//
//inline float distance(Stroke* p1, Stroke* p2)
//{
//	return distance(p1->x, p1->y, p2->x, p2->y);
//}
//
//
//inline float lerp(float a, float b, float f)
//{
//	return a + f*(b - a);
//}
//
////void draw(Stroke* p1, Stroke* p2)
////{
////	float dist = distance(p1, p2);
////	if (equalZero(dist))
////		return;
////	float c = dist / 30.0f;
////	float step = 1.0f;
////	if (c > step)
////		c = step;
////	float t = 0.0f;
////	float xt = p1->x, yt = p1->y, rt = p2->pressure;
////	int sum = 0;
////	while (dist > t)
////	{
////		float b = powf(t/dist, 3.0);
////		xt = lerp(p1->x, p2->x, b);
////		glLineWidth(p2->pressure);
////	}
////}
//
//void draw(Stroke* p1, Stroke* p2)
//{
//	Debugger::write("p1.id", p1->id);
//	Debugger::write("p2.id", p2->id);
//	glLineWidth(p2->pressure);
//	glVertex2d(p1->x, p1->y);
//	glVertex2d(p2->x, p2->y);
//}
//
//void StrokesWindow::render()
//{
//	static Stroke* previous = 0;
//	if (previous)
//	{
//		glEnable(GL_LINE_SMOOTH);
//		glHint(GL_LINE_SMOOTH, GL_NICEST);
//		glBegin(GL_LINE);
//		{
//			draw(previous, stroke());
//		}
//		glEnd();
//	}
//	previous = stroke();
//}
