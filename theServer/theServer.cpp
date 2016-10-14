// theServer.cpp : main project file.

#include "stdafx.h"
#include "doServerSocket.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"Server started:                    OK!");
	DoServerSocket ^ socketWorker = gcnew DoServerSocket();
	return 0;
}
