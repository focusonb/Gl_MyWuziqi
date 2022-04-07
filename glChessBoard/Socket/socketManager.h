#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>

class SocketMediator;
class SocketThread
{
private:
	SOCKADDR_IN loopAdr, clntAdr, servAdr;
	WSADATA wsaData;
	SOCKET hServSock;
	WSAEVENT newEvent;
	WSANETWORKEVENTS netevent;
	char msg[100];
	bool stopwait = true;

public:
	SocketThread() = delete;
	SocketThread(SocketMediator* mediator, ADDRESS_FAMILY sin_family = AF_INET,
		u_long address = 0x7f000001, 
		const char* port = "8198");
	~SocketThread() {
		delete _mediator;
	};
	void sendData(const char* msg);//input
	void reactToMessage(const char* msg, SocketMediator* mediator);//output
private:
	void looprecvsend(SOCKET&sock, WSAEVENT&event, WSANETWORKEVENTS&netevent, char*msg, int size);
	SOCKET& getsocket();
	SOCKADDR_IN getClient();

	SocketMediator* _mediator;//custom interface
};