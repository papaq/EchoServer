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
		return gcnew ResultStc(false, "Send message: NO\nSocket in not connected");
	}

	DoSocket::SendMessage(DoSocket::_socket);

	return gcnew ResultStc(false, "Send message: OK!\n");
}

DoSocket::ResultStc ^ DoClientSocket::ReceiveMessage()
{
	if (!_socket->Connected)
	{
		return gcnew ResultStc(false, "Receive message: NO\nSocket in not connected\n");
	}

	DoSocket::ReceiveMessage(_socket);

	return gcnew ResultStc(false, "Receive message: OK!\n");
}

String ^ DoClientSocket::ExCommute()
{
	DoClientSocket::ResultStc ^ resultHere;
	resultHere = DoClientSocket::ConnectSocket();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return gcnew String("");
	}

	resultHere = DoClientSocket::SendMessage();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return gcnew String("");
	}

	resultHere = DoClientSocket::ReceiveMessage();

	IOConsole::Write(resultHere->output);
	if (!resultHere->correct)
	{
		return gcnew String("");
	}

	return gcnew String(("Message received from server: {0}", DoSocket::_ToReceiveMessage));
}

