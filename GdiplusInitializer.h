#pragma once

class GdiplusInitializer
{
public:
	GdiplusInitializer();
	~GdiplusInitializer();
private:
	ULONG_PTR token_;
};


class ComInitializer
{
public:
	ComInitializer();
	~ComInitializer();

};
