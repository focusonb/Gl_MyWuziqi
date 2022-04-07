#pragma comment(lib, "Ws2_32.lib")

#include "SocketManager.h"
#include <string>

#include "CommonFunction.h"
#include "socketMediator.h"

using std::string;

SocketThread::SocketThread(SocketMediator* mediator, ADDRESS_FAMILY sin_family, u_long address, const char* port)
{
	_mediator = mediator->clone();
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = sin_family;
	//servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_addr.s_addr = htonl(address);
	//servAdr.sin_addr.s_addr = htonl(0x84a10068);
	servAdr.sin_port = htons(atoi(port));
	//(*((*((Threadarg_iswin*)arg)).semathree)).acquire();
	if (::connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) != SOCKET_ERROR)
	{

		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		//do sth,i.e. send a fisrt message to server

		looprecvsend(hServSock, newEvent, netevent, msg, sizeof(msg));
	}
	else
	{
		SOCKET loopsock = socket(PF_INET, SOCK_STREAM, 0);
		memset(&loopAdr, 0, sizeof(loopAdr));
		loopAdr.sin_family = AF_INET;
		loopAdr.sin_addr.s_addr = htonl(INADDR_ANY);
		loopAdr.sin_port = htons(atoi("9198"));
		if (::bind(loopsock, (SOCKADDR*)&loopAdr, sizeof(loopAdr)) == SOCKET_ERROR)
		{
			ErrorHandling("bind error\n");
			return;
		}
		if (::listen(loopsock, 5) == SOCKET_ERROR)
		{
			ErrorHandling("listen error\n");
			return;
		}
		int clntAdrLen = sizeof(clntAdr);
		hServSock = ::accept(loopsock, (SOCKADDR*)&clntAdr, &clntAdrLen);
		if (hServSock == SOCKET_ERROR)
		{
			ErrorHandling("accept error\n");
			return;
		}
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		looprecvsend(hServSock, newEvent, netevent, msg, sizeof(msg));//wait for client connecting in
	}
	return;
}

void SocketThread::sendData(const char * msg)
{
	string msgStr(msg);
	send(hServSock, msg, sizeof(msg), 0);
}

void SocketThread::reactToMessage(const char * msg, SocketMediator* mediator)
{
	mediator->processMsg(msg);
}

void SocketThread::looprecvsend(SOCKET&sock, WSAEVENT&event, WSANETWORKEVENTS&netevent, char*msg, int size)
{// loop and proccess evnets
	while (1)
	{
		WSAWaitForMultipleEvents(1, &event, false, WSA_INFINITE, FALSE);
		WSAEnumNetworkEvents(sock, event, &netevent);
		if (netevent.iErrorCode[FD_READ_BIT] != 0)
		{
			ErrorHandling("read error\n");
			break;
		}
		int strlen = recv(sock, msg, size, 0);
		//string recstr(msg);
		//do sth
		reactToMessage(msg, _mediator);
	}
}

SOCKET & SocketThread::getsocket()
{
	return hServSock;
}

SOCKADDR_IN SocketThread::getClient()
{
	return clntAdr;
}
