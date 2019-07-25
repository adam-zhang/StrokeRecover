#pragma once
//#include "Global.h"
#include <vector>
#include <iostream>

//#define WM_SOCKET_MSG (WM_USER+201)
#define RANDMOD(x) (rand()%(x))
enum PEN_STATUS : int
{
	PEN_UP = 0,
	PEN_DOWN,
	PEN_MOVE,
	PEN_OVER
};

class Stroke
{
public:
	int id;
	float x;
	float y;
	float pressure;
	unsigned __int64 timestamp;
	unsigned __int64 timestamp1;
	//std::string timestamp;
	PEN_STATUS status;//0,up 1,down 2,move 3,over
	bool operator==(const Stroke& rhs)
	{
		return (*this).id == rhs.id;
	}
	bool operator<(const Stroke& rhs)
	{
		return (*this).id < rhs.id;
	}
	bool operator>(const Stroke& rhs)
	{
		return (*this).id > rhs.id;
	}
}; // STROKE, *PSTROKE;

std::ostream& operator<<(std::ostream& out, const Stroke& stroke);

struct InitInfo
{
	int maxX;
	int maxY;
	int maxPressure;
	float min_pen_width;
	float max_pen_width;
	std::string clientIP;
}; // INITINFO;

//extern INITINFO g_initInfoData;


//extern std::vector<STROKE> m_totalData;
//extern std::vector<STROKE> m_strokeData;
//extern std::vector<STROKE> m_drawData;

extern int cleanFlag;

extern volatile int completeFlag;

extern std::string android_ip;
//extern int suspendCount;
//extern HWND pMainWnd;