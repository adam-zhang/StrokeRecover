#include "stdafx.h"
#include "Strokes.h"
#include "Debugger.h"

using namespace std;

Strokes::Strokes()
	: allowPost_(true)
{
}


Strokes::~Strokes()
{
}


std::mutex Strokes::m;
std::shared_ptr<Strokes> Strokes::instance_;


const STROKE Strokes::pop()
{
	std::lock_guard<std::mutex> lock(protector_);
	lock;
	auto e = out_.front();
	out_.erase(out_.begin());
	return e;
}

void Strokes::push(const STROKE& value)
{
	lock_guard<mutex> lock(protector_);
	in_.push_back(value);
}


void Strokes::switchVector()
{
	std::lock_guard<std::mutex> lock(protector_);
	lock;
	auto temp = in_;
	in_ = out_;
	out_ = temp;
}

bool Strokes::empty()
{
	lock_guard<mutex> lock(protector_);
	lock;
	return out_.empty();
}


size_t Strokes::size()
{
	return out_.size();
}
