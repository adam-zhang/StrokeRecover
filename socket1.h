//#pragma once
//#include <string.h>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
//
//using boost::asio::ip::tcp;
//using boost::asio::ip::address;
//
//class session : public boost::enable_shared_from_this<session> {
//public:
//	session(boost::asio::io_service &io_service);
//	~session();
//	void start();
//	//void stop();
//	tcp::socket &socket();
//
//private:
//	void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
//
//	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
//
//private:
//	tcp::socket socket_;
//	boost::asio::streambuf sbuf_;
//	//char sbuf_[128];
//};
//
//typedef boost::shared_ptr<session> session_ptr;
//
//class server {
//public:
//	~server();
//	server(boost::asio::io_service &io_service, tcp::endpoint &endpoint);
//
//	void handle_accept(session_ptr new_session, const boost::system::error_code& error);
//	//void write_msg(std::string msg);
//	void run();
//	void stop();
//
//private:
//	boost::asio::io_service &io_service_;
//	tcp::acceptor acceptor_;
//	bool bend;
//	//boost::asio::ip::tcp::endpoint _ep;
//	//typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;
//};

