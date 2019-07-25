#include "stdafx.h"
#include "GdiplusInitializer.h"
#include <gdiplus.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

GdiplusInitializer::GdiplusInitializer()
	: token_(0)
{
	Gdiplus::GdiplusStartupInput input;
	Gdiplus::GdiplusStartup(&token_, &input, NULL);
}


GdiplusInitializer::~GdiplusInitializer()
{
	if (!token_)
		Gdiplus::GdiplusShutdown(token_);
}

GdiplusInitializer gdiplusInitializer;


ComInitializer::ComInitializer()
{
	CoInitialize(NULL);
}

ComInitializer::~ComInitializer()
{
	CoUninitialize();
}

ComInitializer comInitializer;
