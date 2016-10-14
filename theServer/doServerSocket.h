#pragma once

#include "doSocket.h"

ref class DoServerSocket : DoSocket
{
	DoServerSocket::ResultStc ^ ListeningSocket();

	void Acceptor();

	DoServerSocket::ResultStc ^ EchoRequest(Socket ^ currentSocket);

	void ExCommute();
public:
	DoServerSocket();

};

