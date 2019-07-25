#ifndef __SOCKET_SERVER__H
#define __SOCKET_SERVER__H

#include <vector>
#include <atomic>

class SocketServer
{
public:
	explicit SocketServer(short port);
	~SocketServer();
private:
	short port_;
	SOCKET s_;
	std::atomic<bool> stop_;
private:
	SOCKET createSocket(short port);
public:
	void run();
	void stopSocket()
	{
		stop_ = true;
	}
private:
	void processData(SOCKET client);
private:
};
void startSocketServer(short);
void  stopSocketServer();
#endif//__SOCKET_SERVER__H