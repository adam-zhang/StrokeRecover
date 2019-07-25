//#pragma once
//#include <string.h>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
//
//class trans_server
//{
//	boost::asio::ip::tcp::acceptor _acceptor;
//	boost::asio::ip::tcp::socket _sock;
//public:
//	trans_server(boost::asio::io_service& io_serv,
//		const boost::asio::ip::tcp::endpoint& addrport);
//private:
//	void do_accept();
//};
//
//class trans_session : public std::enable_shared_from_this<trans_session>
//{
//	boost::asio::ip::tcp::socket _sock;
//	boost::asio::streambuf sbuf_;
//public:
//	trans_session(boost::asio::ip::tcp::socket s);
//	void start();
//	void do_write(std::string msg);
//private:
//	void do_read_hander();
//	void do_write_hander();
//};
//
//class connection : public boost::enable_shared_from_this<connection>
//{
//	boost::asio::ip::tcp::socket _sock;
//	boost::asio::io_service& _service;
//	bool _bstarted;
//	char _rbuf[128];
//	char _wbuf[128];
//public:
//	connection(boost::asio::io_service& io_serv);
//	void start(boost::asio::ip::tcp::endpoint ep);
//	void stop();
//	inline bool isStarted() { return _bstarted; }
//	void do_read();
//	void do_write(const std::string& msg);
//	
//private:
//	void on_connect(const boost::system::error_code& err);
//	void on_read(const boost::system::error_code& err, std::size_t bytes);
//	void on_write(const boost::system::error_code& err, std::size_t bytes);
//
//	void process_data(const std::string& msg);
//
//};
//void udp_server(int port, std::string msg);
//void udp_client(int port, std::string msg);