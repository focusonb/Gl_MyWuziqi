#pragma comment(lib, "Ws2_32.lib")

#include "SocketManager.h"
#include <string>

#include "CommonFunction.h"
#include "socketMediator.h"

#include <iostream>

using std::string;

bool SocketManager::buidConnection( ADDRESS_FAMILY sin_family, u_long address, const char* port)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
		return false;
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

		looprecvsend();
	}
	else
	{
		SOCKET loopsock = socket(PF_INET, SOCK_STREAM, 0);
		memset(&loopAdr, 0, sizeof(loopAdr));
		loopAdr.sin_family = sin_family;
		loopAdr.sin_addr.s_addr = htonl(INADDR_ANY);
		loopAdr.sin_port = htons(atoi(port));
		if (::bind(loopsock, (SOCKADDR*)&loopAdr, sizeof(loopAdr)) == SOCKET_ERROR)
		{
			ErrorHandling("bind error\n");
			return false;
		}
		if (::listen(loopsock, 5) == SOCKET_ERROR)
		{
			ErrorHandling("listen error\n");
			return false;
		}
		int clntAdrLen = sizeof(clntAdr);
		hServSock = ::accept(loopsock, (SOCKADDR*)&clntAdr, &clntAdrLen);
		if (hServSock == SOCKET_ERROR)
		{
			ErrorHandling("accept error\n");
			return false;
		}
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		looprecvsend();//wait for client connecting in
	}
	return true;
}

void SocketManager::sendMessage(const string& str)
{
	send(hServSock, str.c_str(), str.size(), 0);
}



void SocketManager::looprecvsend()
{// loop and proccess evnets
	while (m_connection)
	{
		std::cout << "enter loop" << std::endl;
		if (WSAWaitForMultipleEvents(1, &newEvent, false, 1000, FALSE) == WSA_WAIT_TIMEOUT)
			continue;
		WSAEnumNetworkEvents(hServSock, newEvent, &netevent);
		if (netevent.iErrorCode[FD_READ_BIT] != 0)
		{
			ErrorHandling("read error\n");
			continue;
		}
		recv(hServSock, msg, sizeof(msg), 0);
		writeBuffer(msg);
		memset(msg, 0, sizeof(msg));
	}
	closesocket(hServSock);
}

list<string> SocketManager::readBuffer()
{
	lock_guard<mutex> mtx(m_mtx);
	return std::move(m_buffer);
}

void SocketManager::writeBuffer(char * message)
{
	string msg(message);
	lock_guard<mutex> mtx(m_mtx);
	m_buffer.push_back(msg);
}

SOCKET & SocketManager::getsocket()
{
	return hServSock;
}

SOCKADDR_IN SocketManager::getClient()
{
	return clntAdr;
}
