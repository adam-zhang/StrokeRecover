#pragma once
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include "ThreadSafeQueue.h"

struct InitInfo;
class Stroke;

class GlobalVariable
{
private:
	GlobalVariable();
public:
	~GlobalVariable();
public:
private:
	static std::shared_ptr<GlobalVariable> instance_;
	static std::mutex m_;
public:

	static GlobalVariable& instance();
private:
	std::shared_ptr<InitInfo> initInfo_;
	//std::vector<std::shared_ptr<Stroke>> strokes_;
	CWnd* messageWindow_;
	//ThreadSafeQueue<Stroke*> queue_;
public:
	void setMessageWindow(CWnd* value)
	{
		messageWindow_ = value;
	}
	CWnd* messageWindow()const
	{
		return messageWindow_;
	}
	void pushStroke(Stroke* value);
	Stroke* popStroke();
	void clearStrokes();
	bool strokesEmpty();
	//std::shared_ptr<Stroke> strokes(size_t value);
	//size_t addStroke(const std::shared_ptr<Stroke>& value)
	//{
	//	strokes_.push_back(value);
	//	return strokes_.size() - 1;
	//}
	const std::shared_ptr<InitInfo>& initInfo()const
	{
		return initInfo_;
	}
	void setInitInfo(const std::shared_ptr<InitInfo>& value)
	{
		initInfo_ = value;
	}

};

