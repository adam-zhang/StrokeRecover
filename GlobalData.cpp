#include "stdafx.h"

#include "GlobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#include "Global.h"




//INITINFO g_initInfoData;


//std::vector<STROKE> m_totalData;
//std::vector<STROKE> m_strokeData;
//std::vector<STROKE> m_drawData;

//int cleanFlag = 0;
//volatile int completeFlag = 0;
//int suspendCount=0;

//HWND pMainWnd;
//bool bRealtime = false;
//std::string android_ip="";

std::ostream& operator<<(std::ostream& out, const Stroke& stroke)
{
	out << stroke.id << ","
		<< stroke.x << ","
		<< stroke.y << ","
		<< stroke.pressure << ","
		<< stroke.timestamp << ","
		<< stroke.timestamp1 << ","
		<< stroke.status;
	return out;
}
