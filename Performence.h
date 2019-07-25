#pragma once
#include <ctime>
#include <sstream>
#include <Windows.h>
#include "Debugger.h"


class Performence
{
public:
	explicit Performence(const std::wstring& functionName)
		: time_(0)
		, functionName_(functionName)
		, elapsed_(false)
	{
		time_ = GetTickCount();
	}
	~Performence()
	{
		if (!elapsed_)
			elapsed();
	}

public:
	void elapsed()
	{
		auto elapse = GetTickCount() - time_;
		std::wstringstream ws;
		ws << functionName_ << " elapsed time:" << elapse << std::endl;
		Debugger::write(ws.str());
		elapsed_ = true;
	}
private:
	DWORD time_;
	std::wstring functionName_;
	bool elapsed_;
};

