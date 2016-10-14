#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Net;
using namespace System::Net::Sockets;

ref class DoSocket
{
public:
	value struct ResultStc
	{
		bool correct;
		String ^ output;
		ResultStc(bool f, String ^ out)
		{
			this->correct = f;
			this->output = out;
		}
	};

private:
	String ^ SERVER = "127.0.20.1";
	const int PORT = 32100;
	
public:
	DoSocket();
	DoSocket(String ^ toSendMsg);

protected:
	String ^ _ToSendMessage, ^ _ToReceiveMessage;
	IPEndPoint ^ _endPoint;
	Socket ^ _socket;

	void CreateSocket();
	void ReceiveMessage(Socket ^ currentSocket);
	void SendMessage(Socket ^ currentSocket);
};

