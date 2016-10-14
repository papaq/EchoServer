#include "stdafx.h"
#include "doSocket.h"


DoSocket::DoSocket()
{
}

void DoSocket::CreateSocket()
{
	IPAddress ^ address = IPAddress::Parse(SERVER);
	_endPoint = gcnew IPEndPoint(address, PORT);
	_socket = gcnew Socket(_endPoint->AddressFamily, SocketType::Stream, ProtocolType::Tcp);

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

	_ToReceiveMessage = receivedMessage;
}

void DoSocket::SendMessage(Socket ^ currentSocket)
{
	array<Byte> ^ bytesToSend = Encoding::ASCII->GetBytes(_ToSendMessage);

	currentSocket->Send(bytesToSend, bytesToSend->Length, static_cast<SocketFlags>(0));
}
