#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <string>
#include <list>
#include <mutex>
//#include <thread>

using std::list;
using std::string;
using std::mutex;
using std::lock_guard;

class SocketManager
{
private:
	SOCKADDR_IN loopAdr, clntAdr, servAdr;
	WSADATA wsaData;
	SOCKET hServSock;
	WSAEVENT newEvent;
	WSANETWORKEVENTS netevent;
	char* msg;
	list<string> m_buffer;
	mutex m_mtx;
	bool stopwait = true;
	volatile bool m_connection;

public:
	SocketManager():msg(new char[1000]), m_connection(true){};
	bool buidConnection(ADDRESS_FAMILY sin_family,
		u_long address, 
		const char* port);
	~SocketManager() {
		delete msg;
	};
	void sendMessage(const char* msg);//input
	void close() { m_connection = false; }
	list<string> readBuffer();
private:
	void looprecvsend();
	void writeBuffer(char* message);
	SOCKET& getsocket();
	SOCKADDR_IN getClient();

};