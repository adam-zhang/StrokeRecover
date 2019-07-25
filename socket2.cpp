#include "stdafx.h"
//#include "socket2.h"
//#include "Performence.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
//
//trans_server::trans_server(boost::asio::io_service& io_serv,
//	const boost::asio::ip::tcp::endpoint& addrport)
//	:_acceptor(io_serv, addrport),
//	_sock(io_serv)
//{
//	do_accept();
//}
//
//void trans_server::do_accept()
//{
//	_acceptor.async_accept(_sock, [this](boost::system::error_code ec)
//	{
//		if (!ec)
//		{
//			auto ep = _sock.remote_endpoint();
//			//
//			std::make_shared<trans_session>(std::move(_sock))->start();//session
//		}
//
//		do_accept();
//	}
//	);
//}
//
//
//
//
//trans_session::trans_session(boost::asio::ip::tcp::socket s)
//	:_sock(std::move(s))
//{
//
//}
//void trans_session::start()
//{
//	do_read_hander();
//	
//}
//void trans_session::do_write(std::string msg)
//{
//	//sbuf_
//	std::ostream trans(&sbuf_);
//	trans << msg;
//	do_write_hander();
//}
//void trans_session::do_read_hander()
//{
//	Performence p(TEXT("do_read_handler"));
//	p;
//	auto self(shared_from_this());
//	boost::asio::async_read(_sock, sbuf_, [this, self](boost::system::error_code ec, std::size_t)
//	{
//		if (!ec)
//		{
//			do_read_hander();
//		}
//		else
//		{
//			//error
//		}
//	} );
//}
//void trans_session::do_write_hander()
//{
//	auto self(shared_from_this());
//	boost::asio::async_write(_sock,
//		sbuf_,
//		[this, self](boost::system::error_code ec, std::size_t)
//	{
//		if (!ec)
//		{
//			//std::cout << "write complete" << std::endl;
//		}
//		else
//		{
//			//error
//		}
//	}
//		);
//	//sock_.async_write_some(buffer(write_buffer_, msg.size()), boost::bind(&trans_session::do_write, shared_from_this(), _1, _2));
//}
//
//
//connection::connection(boost::asio::io_service& io_serv)
//	:_service(io_serv),
//	_sock(io_serv),
//	_bstarted(true)
//{
//
//}
//void connection::start(boost::asio::ip::tcp::endpoint ep)
//{
//	_sock.async_connect(ep, boost::bind(&connection::on_connect, shared_from_this(),_1));
//}
//void connection::stop()
//{
//	if (!_bstarted)
//		return;
//	_bstarted = false;
//	_sock.close();
//}
//void connection::do_read()
//{
//	_sock.async_read_some(boost::asio::buffer(_rbuf), boost::bind(&connection::on_read, shared_from_this(), _1, _2));
//}
//void connection::do_write(const std::string& msg)
//{
//	if (!_bstarted)
//		return;
//	std::copy(msg.begin(), msg.end(), _wbuf);
//	_sock.async_write_some(boost::asio::buffer(_wbuf, msg.size()), boost::bind(&connection::on_write, shared_from_this(),_1, _2));
//}
//void connection::on_connect(const boost::system::error_code& err)
//{
//	if (!err)
//		do_read();
//	else
//		stop();
//}
//void connection::on_read(const boost::system::error_code& err, std::size_t bytes)
//{
//	if (!_bstarted)
//		return;
//	std::string msg(_rbuf, bytes);
//	if (msg.size() > 0)
//	{
//		process_data(msg);
//	}
//	//else
//	//{
//	//	stop();
//	//}
//}
//void connection::on_write(const boost::system::error_code& err, std::size_t bytes)
//{
//	//write completely, need I to get the feedback data ?
//	do_read();
//}
//void connection::process_data(const std::string& msg)
//{
//	//parse the msg
//	std::string val = msg;
//}
//
//
////broadcast 
////server
//void handle_send() {}
//void handle_recv() {}
//void udp_server(int port,std::string msg)
//{
//	boost::asio::io_service io_service;
//	boost::asio::ip::udp::socket udp_sock(io_service,
//		boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
//	udp_sock.set_option(boost::asio::socket_base::broadcast(true));
//	boost::asio::ip::udp::endpoint broadcast_ep(boost::asio::ip::address_v4::broadcast(), port);
//	//boost::array<char, 128> buf;
//	udp_sock.async_send_to(boost::asio::buffer(msg,msg.size()), broadcast_ep, boost::bind(&handle_send));
//	io_service.run();
//}
//
////client
//void udp_client(int port, std::string msg)
//{
//	boost::asio::io_service _ioservice;
//	boost::asio::ip::udp::socket udp_sock(_ioservice,
//		boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
//	boost::asio::ip::udp::endpoint send_ep;
//
//	char buf[128]{ 0 };
//	udp_sock.async_receive_from(boost::asio::buffer(buf),send_ep,boost::bind(&handle_recv));
//	_ioservice.run();
//}