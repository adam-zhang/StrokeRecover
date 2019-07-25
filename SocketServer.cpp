#include "stdafx.h"
#include "SocketServer.h"
#include "GlobalVariable.h"
#include "Messages.h"
#include "Debugger.h"
#include "GlobalData.h"
#include "StrokeFactory.h"
#include "Performence.h"
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


SocketServer::SocketServer(short port)
	:port_(port)
	, s_(INVALID_SOCKET)
	, stop_(false)
{
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);
}

SocketServer::~SocketServer()
{
	if (s_ != INVALID_SOCKET)
		closesocket(s_);
	WSACleanup();
}
//
SOCKET SocketServer::createSocket(short port)
{
	auto s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
		return s;
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.S_un.S_addr = INADDR_ANY;
	auto ret = bind(s, (LPSOCKADDR)&address, sizeof(address));
	if (ret == SOCKET_ERROR)
	{
		closesocket(s);
		Debugger::write("bind error", WSAGetLastError());
		return INVALID_SOCKET;
	}
	ret = listen(s, 5);
	if (ret == SOCKET_ERROR)
	{
		closesocket(s);
		Debugger::write("listen error", WSAGetLastError());
		return INVALID_SOCKET;
	}
	return s;
}
//
void postMessage(size_t command, WPARAM wParam, LPARAM lParam)
{
	if (!GlobalVariable::instance().messageWindow())
		return;
	Debugger::construct();
	PostMessage(GlobalVariable::instance().messageWindow()->m_hWnd, command, wParam, lParam);
}

void processInitInfo(const std::vector<std::string>& data)
{
	auto p = std::make_shared<InitInfo>();
	p->maxPressure = atoi(data[1].c_str());
	p->min_pen_width = 0.2f;
	p->max_pen_width = 3.0f;
	p->maxX = atoi(data[4].c_str());
	p->maxY = atoi(data[5].c_str());
	p->clientIP = data[6];
	GlobalVariable::instance().setInitInfo(p);
	postMessage(WM_SOCKET_MSG, WPARAM(COMMAND_START), LPARAM(0));
}

void processStrokes(const std::vector<std::string>& data)
{
	auto p = StrokeFactory::instance().getStroke();
	assert(p);
	p->id = atoi(data[0].c_str());
	static boost::posix_time::ptime time_now;
	boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
	if (p->id == 1)	
		time_now = boost::posix_time::microsec_clock::universal_time();
	p->x = static_cast<float>(atof(data[1].c_str()));
	p->y = static_cast<float>(atof(data[2].c_str()));
	p->pressure = static_cast<float>(atof(data[3].c_str()));
	p->timestamp1 = atoll(data[4].c_str());
	time_elapse = boost::posix_time::microsec_clock::universal_time() - time_now;
	p->timestamp = time_elapse.ticks() / 1000;
	p->status = PEN_STATUS(atoi(data[5].c_str()));
	time_now = boost::posix_time::microsec_clock::universal_time();
	postMessage(WM_SOCKET_MSG, WPARAM(COMMAND_DRAWING), LPARAM(p));
}
//
void processStrokes(const std::string& data)
{
	if (data.empty())
		return;
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of(","), boost::token_compress_on);
	if (vec[0] == "0")
		processInitInfo(vec);
	else
		processStrokes(vec);
}
//
void clear()
{
	//Debugger::write("clear");
	postMessage(WM_SOCKET_MSG, COMMAND_CLEAR, 0);
}

void done()
{
	//Debugger::write("done");
	postMessage(WM_SOCKET_MSG, COMMAND_STOP, 0);
}
//
void processData(const std::string& data)
{
	if (boost::starts_with(data, "over"))
		clear();
	else if (boost::starts_with(data, "done"))
		done();
	else
		processStrokes(data);
}
//
//
void SocketServer::processData(SOCKET client)
{
	const static size_t bufferSize = 256;
	char buffer[256] = { 0 };
	auto length = recv(client, &buffer[0], bufferSize, 0);
	if (length == 0)
		return;
	::processData(&buffer[0]);
	//Debugger::write("data", &buffer[0]);
}
//
void SocketServer::run()
{
	s_ = createSocket(port_);
	if (s_ == -1)
		return;
	while(!stop_)
	{
		struct sockaddr_in clientAddress;
		int length = sizeof(clientAddress);
		Performence p(TEXT("socket elapsed:"));
		auto client = accept(s_, (LPSOCKADDR)&clientAddress, &length);
		p.elapsed();
		processData(client);
		closesocket(client);
	}
	closesocket(s_);
	s_ = INVALID_SOCKET;
}

static std::shared_ptr<SocketServer> server;

void startSocketServer(short port)
{
	server = std::make_shared<SocketServer>(port);
	server->run();
}

void stopSocketServer()
{
	server->stopSocket();
	server.reset();
}
