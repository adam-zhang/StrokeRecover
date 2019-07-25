#pragma once
#include <memory>
#include <vector>

class Stroke;
class Gdiplus::Bitmap;
class DrawingSingleValue;


//void paintStroke(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&, Stroke*);
//void clearStroke(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&);
//void paintStrokeX(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&, Stroke*);

class Painter
{
public:
	virtual void draw(CWnd* window, std::shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke*) = 0;
	virtual void clear(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&) = 0;
};

class SingleValuePainter : public Painter
{
public:
	SingleValuePainter()
		: index_(0)
		, ratio_(1)
	{

	}
public:
	size_t index()
	{
		return index_;
	}

	void setIndex(size_t value)
	{
		index_ = value;
	}
	float ratio()
	{
		return ratio_;
	}
	void shrink()
	{
		ratio_ *= 1.5f;
	}
	std::vector<float> storedValues()
	{
		return storedValues_;
	}
	void storeValue(float value)
	{
		storedValues_.push_back(value);
	}

	void clean()
	{
		index_ = 0;
		storedValues_.clear();
	}
	//virtual void redraw(CWnd*, shared_ptr<Gdiplus::Bitmap>&) = 0;
	//virtual float calculateX(float, float) = 0;
	//virtual float calculateY(float, float) = 0;
private:
	size_t index_;
	float ratio_;
	std::vector<float> storedValues_;
protected:
};
//
class StrokesPainter : public Painter
{
public:
	void draw(CWnd*, std::shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke*);
	virtual void clear(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&);
};

class StrokesXPainter : public SingleValuePainter
{
public:
	void draw(CWnd* window, std::shared_ptr<Gdiplus::Bitmap>& bitmap, Stroke*);
	void clear(CWnd*, std::shared_ptr<Gdiplus::Bitmap>&);
	void redraw(CWnd* window, std::shared_ptr<Gdiplus::Bitmap>& bitmap);
private:
	float calculateX(float,float);
	float calculateY(float,float);
};
//
//class StrokesYPainter : public SingleValuePainter
//{
//public:
//	void draw(std::shared_ptr<Gdiplus::Bitmap>& bitmap, const std::shared_ptr<Stroke>&);
//	virtual void clear(std::shared_ptr<Gdiplus::Bitmap>&);
//	virtual float calculateX(float,float) = 0;
//	virtual float calculateY(float,float) = 0;
//};
//
//class StrokesPressurePainter : public SingleValuePainter
//{
//public:
//	void draw(std::shared_ptr<Gdiplus::Bitmap>& bitmap, const std::shared_ptr<Stroke>&);
//	virtual void clear(std::shared_ptr<Gdiplus::Bitmap>&);
//	virtual float calculateX(float,float) = 0;
//	virtual float calculateY(float,float) = 0;
//};

