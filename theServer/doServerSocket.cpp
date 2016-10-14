#include "stdafx.h"
#include "doServerSocket.h"
#include "ioConsole.h"

DoServerSocket::ResultStc ^ DoServerSocket::ListeningSocket()
{
	DoSocket::CreateSocket();

	try
	{
		this->_socket->Bind(this->_endPoint);
	}
	catch (Exception ^)
	{
		return gcnew ResultStc(false, String::Concat("Associate socket with endpoint:   FAIL\n", 
			"Something went wrong\n"));
	}

	this->_socket->Listen(5);
	return gcnew ResultStc(true, String::Concat("Associate socket with endpoint:    OK!\n",
		"Set to listen to socket:           OK!\n"));
}

void DoServerSocket::Acceptor()
{
	while (true)
	{
		IOConsole::WriteLine("Listening to socket...");

		Socket ^ newSoc;
		try
		{
			newSoc = this->_socket->Accept();
		}
		catch (Exception^)
		{
			IOConsole::Write("Accept socket: FAIL\nSomething went wrong\n");
			return;
		}

		DoServerSocket::ResultStc ^ resultHere;
		resultHere = DoServerSocket::EchoRequest(newSoc);
		if (resultHere->correct)
		{
			IOConsole::Write(String::Concat("Message accepted:                  OK!\n", 
				"Message: \"", this->_ToReceiveMessage->ToString(), "\"\n"));
			IOConsole::Write(resultHere->output);
			IOConsole::WriteLine("Socket closed:                     OK!\n");
		}
		else
		{
			IOConsole::Write(resultHere->output);
			return;
		}
	}

	IOConsole::Write("Accepting sockets completed\n");
}

DoServerSocket::ResultStc ^ DoServerSocket::EchoRequest(Socket ^ currentSocket)
{
	if (currentSocket == nullptr)
	{
		return gcnew ResultStc(false, "ECHO: FAIL\nSomething went wrong\n");
	}

	// Receive message from the socket
	DoSocket::ReceiveMessage(currentSocket);

	this->_ToSendMessage = this->_ToReceiveMessage;

	// Send the same message to the socket
	DoSocket::SendMessage(currentSocket);

	currentSocket->Shutdown(SocketShutdown::Both);
	currentSocket->Close();
	// TODO: insert return statement here

	return gcnew ResultStc(true, "ECHO:                              OK!\n");
}

void DoServerSocket::ExCommute()
{
	DoServerSocket::ResultStc ^ resultHere;
	resultHere = DoServerSocket::ListeningSocket();

	IOConsole::Write(resultHere->output);

	if (!resultHere->correct)
	{
		return;
	}

	DoServerSocket::Acceptor();
}

DoServerSocket::DoServerSocket()
{
	ExCommute();
}
