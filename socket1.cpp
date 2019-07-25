//
#include "stdafx.h"
//#include"socket1.h"
//
//#include "GlobalData.h"
//#include "boost/algorithm/string.hpp"
//#include "boost/thread.hpp"
//#include "boost/timer.hpp"
//#include "Debugger.h"
////#include "Performence.h"
//#include "Strokes.h"
//#include "Messages.h"
//#include "GlobalObject.h"
//#include "GlobalVariable.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//extern HWND pMainWnd;
////extern bool bRealtime;
//
//session::session(boost::asio::io_service &io_service) : socket_(io_service)
//{
//}
//session::~session()
//{
//	//socket_.shutdown(boost::asio::socket_base::shutdown_both);
//	//socket_.close();
//}
//void session::start() 
//{
//	static tcp::no_delay option(true);
//	socket_.set_option(option);
//	boost::asio::async_read(socket_, sbuf_, 
//		boost::bind(
//			&session::handle_read, 
//			shared_from_this(),
//			boost::asio::placeholders::error,
//			boost::asio::placeholders::bytes_transferred));
//}
////void session::stop()
////{
////	socket_.close();
////}
//tcp::socket &session::socket() 
//{
//	return socket_;
//}
//
//
//void session::handle_write(const boost::system::error_code& error, size_t bytes_transferred) 
//{
//	//boost::asio::async_read_until(socket_,
//	//	sbuf_,
//	//	"\n",
//	//	boost::bind(&session::handle_read,
//	//		shared_from_this(),
//	//		boost::asio::placeholders::error,
//	//		boost::asio::placeholders::bytes_transferred));
//	boost::asio::async_read(socket_,
//		sbuf_,
//		boost::bind(&session::handle_read,
//			shared_from_this(),
//			boost::asio::placeholders::error,
//			boost::asio::placeholders::bytes_transferred));
//}
//
//void session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) 
//{
//	//Performence p(TEXT("handle_read"));
//	//p;
//	static boost::posix_time::ptime time_now;
//	boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
//
//	std::vector<std::string> vecStr;
//	boost::asio::streambuf::const_buffers_type cbt = sbuf_.data();
//	std::string _data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
//	if (_data.length() > 0)
//	{
//		if (_data == "over")
//		{
//			//GetForegroundWindow()
//			//::FindWindow(NULL, _T("AXSign Restore"));
//			//::PostMessageW(::FindWindowW(NULL, L"AXSign Restore"), WM_SOCKET_MSG,WPARAM(1),LPARAM(0));
//			::PostMessage(GlobalVariable::instance().messageWindow()->m_hWnd, WM_SOCKET_MSG, WPARAM(COMMAND_CLEAR), LPARAM(0));
//		}
//		else if (_data.find("done") != std::string::npos)
//		{
//			
//			 int flag = std::stoi(_data.substr(5, 1));
//			::PostMessage(GlobalVariable::instance().messageWindow()->m_hWnd, WM_SOCKET_MSG, WPARAM(COMMAND_STOP), LPARAM(flag));
//		}
//		else
//		{
//			boost::split(vecStr, _data, boost::is_any_of(","));
//			if (vecStr[0] == "0")
//			{
//				auto p = std::make_shared<InitInfo>();
//				p->maxPressure = atoi(vecStr[1].c_str());
//				p->min_pen_width = 0.2f;
//				p->max_pen_width = 3.0f;
//				p->maxX = atoi(vecStr[4].c_str());
//				p->maxY = atoi(vecStr[5].c_str());
//				p->clientIP = vecStr[6];
//				GlobalVariable::instance().setInitInfo(p);
//				::PostMessage(GlobalVariable::instance().messageWindow()->m_hWnd, WM_SOCKET_MSG, WPARAM(COMMAND_START), LPARAM(0));
//			}
//			else if (vecStr.size() == 6)
//			{
//				//if (1 == completeFlag)
//				//{
//				//	return;
//				//}
//				auto p = std::make_shared<Stroke>(); // data{ 0 };
//				p->id = atoi(vecStr[0].c_str());
//				if (p->id == 1)	time_now = boost::posix_time::microsec_clock::universal_time();
//				p->x = atof(vecStr[1].c_str());
//				p->y = atof(vecStr[2].c_str());
//				p->pressure = atof(vecStr[3].c_str());
//				p->timestamp1 = atoll(vecStr[4].c_str());
//				time_elapse = boost::posix_time::microsec_clock::universal_time() - time_now;
//				p->timestamp = time_elapse.ticks()/1000;
//				p->status = PEN_STATUS(atoi(vecStr[5].c_str()));
//				time_now = boost::posix_time::microsec_clock::universal_time();
//				auto index = GlobalVariable::instance().addStroke(p);
//				PostMessage(GlobalVariable::instance().messageWindow()->m_hWnd, WM_SOCKET_MSG, WPARAM(COMMAND_DRAWING), index);
//				//GlobalObject::instance().notify_all();
//			}
//		}
//	}
//}
//
//
//
//server::server(boost::asio::io_service &io_service, tcp::endpoint &endpoint)
//	: io_service_(io_service), acceptor_(io_service, endpoint)
//{
//	bend = false;
//	session_ptr new_session(new session(io_service_));
// 	acceptor_.async_accept(new_session->socket(),
//		boost::bind(&server::handle_accept,
//			this,
//			new_session,
//			boost::asio::placeholders::error));
//
//}
//server::~server()
//{
//	stop();
//}
//void server::handle_accept(session_ptr new_session, const boost::system::error_code& error) 
//{
//	if (error) {
//		return;
//	}
//	//_ep = new_session->socket().remote_endpoint();
//	new_session->start();
//	if (bend)
//		return;
//	new_session.reset(new session(io_service_));
//	acceptor_.async_accept(new_session->socket(), boost::bind(&server::handle_accept, this, new_session,
//		boost::asio::placeholders::error));
//}
//
//void server::run() 
//{
//	io_service_.run();
//}
//void server::stop()
//{
//	//if (acceptor_.is_open())
//	//{
//	//	acceptor_.cancel();
//	//	acceptor_.close();
//	//}
//	//io_service_.reset();
//	if(!io_service_.stopped())
//		io_service_.stop();
//	bend = false;
//}