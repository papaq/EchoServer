#include "stdafx.h"
#include "doSocket.h"


DoSocket::DoSocket()
{
}

DoSocket::DoSocket(String ^ toSendMsg)
{
	this->_ToSendMessage = toSendMsg;
}

void DoSocket::CreateSocket()
{
	IPAddress ^ address = IPAddress::Parse(SERVER);
	this->_endPoint = gcnew IPEndPoint(address, PORT);
	this->_socket = gcnew Socket(this->_endPoint->AddressFamily, SocketType::Stream, ProtocolType::Tcp);

}

void DoSocket::ReceiveMessage(Socket ^ currentSocket)
{
	array<Byte> ^ bytesToReceive = gcnew array<Byte>(256);

	String ^ receivedMessage = "";

	int bytes = 0;

	do
	{
		bytes = currentSocket->Receive(bytesToReceive, bytesToReceive->Length, static_cast<SocketFlags>(0));
		receivedMessage = String::Concat(receivedMessage, Encoding::ASCII->GetString(bytesToReceive, 0, bytes));
	} while (bytes > 0);

	this->_ToReceiveMessage = receivedMessage;
}

void DoSocket::SendMessage(Socket ^ currentSocket)
{
	array<Byte> ^ bytesToSend = Encoding::ASCII->GetBytes(this->_ToSendMessage);

	currentSocket->Send(bytesToSend, bytesToSend->Length, static_cast<SocketFlags>(0));
}
