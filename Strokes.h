#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include <algorithm>
#include "GlobalData.h"


//class Strokes 
//{
//public:
//	Strokes();
//	~Strokes();
//private:
//	std::vector<STROKE> out_;
//	std::vector<STROKE> in_;
//	//std::queue<STROKE> q_;
//public:
//	void switchVector();
//
//	const STROKE pop();
//	void push(const STROKE&);
//	bool empty();
//	size_t size();
//private:
//	static std::mutex m;
//	static std::shared_ptr<Strokes> instance_;
//	std::mutex protector_;
//	bool allowPost_;
//private:
//public:
//	static Strokes& instance()
//	{
//		if (!instance_)
//		{
//			m.lock();
//			if (!instance_)
//				instance_ = std::make_shared<Strokes>();
//		}
//		return *instance_;
//	}
//};



