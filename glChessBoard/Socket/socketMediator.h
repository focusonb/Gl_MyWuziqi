#pragma once
class SocketMediator
{
public:
	virtual void processMsg(const char* msg) = 0;
	virtual SocketMediator* clone() = 0;//deep copy;
};


