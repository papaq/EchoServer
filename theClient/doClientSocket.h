#pragma once

#include "doSocket.h"
#include "ioConsole.h"

ref class DoClientSocket : DoSocket
{
	DoClientSocket::ResultStc ^ DoClientSocket::ConnectSocket();
	
	DoSocket::ResultStc ^ SendMessage();

	DoSocket::ResultStc ^ ReceiveMessage();
public:
	DoClientSocket::DoClientSocket() : DoSocket("test message") {};
	DoClientSocket(String ^ message) : DoSocket(message) {};

	String ^ ExCommute();
};

