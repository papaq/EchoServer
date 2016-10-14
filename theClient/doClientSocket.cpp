#include "stdafx.h"
#include "doClientSocket.h"


DoClientSocket::ResultStc ^ DoClientSocket::ConnectSocket()
{
	DoSocket::CreateSocket();

	try
	{
		_socket->Connect(_endPoint);
	}
	catch (Exception ^)
	{
		return gcnew ResultStc(false, "Connect to remote host: FAIL\nSomething went wrong\n");
	}

	return gcnew ResultStc(true, "Connect to remote host: OK!\n");
}

DoSocket::ResultStc ^ DoClientSocket::SendMessage()
{
	if (!_socket->Connected)
	{
		return gcnew ResultStc(false, "Send message: FAIL\nSocket in not connected");
	}

	DoSocket::SendMessage(DoSocket::_socket);

	return gcnew ResultStc(true, "Send message: OK!\n");
}

DoSocket::ResultStc ^ DoClientSocket::ReceiveMessage()
{
	if (!_socket->Connected)
	{
		return gcnew ResultStc(false, "Receive message: FAIL\nSocket in not connected\n");
	}

	DoSocket::ReceiveMessage(_socket);

	return gcnew ResultStc(true, "Receive message: OK!\n");
}

String ^ DoClientSocket::ExCommute()
{
	DoClientSocket::ResultStc ^ resultHere;
	resultHere = DoClientSocket::ConnectSocket();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return("Gone wrong");
	}

	resultHere = DoClientSocket::SendMessage();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return("Gone wrong");
	}

	resultHere = DoClientSocket::ReceiveMessage();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return("Gone wrong");
	}

	return String::Concat("Message received from server: ", this->_ToReceiveMessage);
}

