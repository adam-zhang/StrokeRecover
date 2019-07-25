#include "stdafx.h"
#include "Debugger.h"
#include "CodeConverter.h"
#include "Performence.h"
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

string modulePath()
{
	vector<char> buffer(MAX_PATH);
	//GetModuleFileNameA(AfxGetInstanceHandle(), &buffer[0], MAX_PATH);
	GetModuleFileNameA(NULL, &buffer[0], MAX_PATH);
	string path(&buffer[0]);
	return path.substr(0, path.rfind('\\') + 1);
}

string makeFileName()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	stringstream ss;
	ss << time.wYear
		<< setw(2) << setfill('0') << time.wMonth
		<< setw(2) << setfill('0') << time.wDay
		<< setw(2) << setfill('0') << time.wHour;
	return ss.str();
}

void Debugger::writeFile(const string& text)
{
	try
	{
		auto fileName = modulePath() + makeFileName() + ".txt";
		ofstream file(fileName, ios::out | ios::app);
		if (file.good())
		{
			file << text;
		}
		else
			write("can not open file");
	}
	catch (std::exception& e)
	{
		write(e.what());
	}
}

string dateTime()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	stringstream ss;
	ss << time.wYear << "-" << time.wMonth << "-" << time.wDay
		<< " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond
		<< "." << time.wMilliseconds;
	return ss.str();
}



void doWriteFile(const std::string& notice)
{
	thread t(&Debugger::writeFile, notice);
	t.detach();
}

void Debugger::write(const std::string& notice)
{
	auto out = dateTime() + " " + notice + "\n";
	OutputDebugStringA(out.c_str());
	doWriteFile(out);
}

//void Debugger::write(const std::string& notice, size_t value)
//{
//	std::stringstream ss;
//	ss << notice << ":" << value;
//	write(ss.str());
//}


void Debugger::write(const std::string& notice, const std::string& value)
{
	std::stringstream ss;
	ss << notice << ":" << value;
	write(ss.str());
}


void Debugger::write(const std::wstring& notice)
{
	//MessageBox(NULL, notice.c_str(), TEXT(""), 0);
	write(CodeConverter::Utf16ToAnsi(notice));
}

std::shared_ptr<Performence> Debugger::performence_;

void Debugger::construct()
{
	//performence_ = std::make_shared<Performence>(TEXT("cross thread"));
}
void Debugger::deconstruct()
{
	//performence_.reset();
}
