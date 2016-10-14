#include "stdafx.h"
#include "ioConsole.h"


IOConsole::IOConsole()
{
}

void IOConsole::Write(String ^ str)
{
	Console::Write(str);
}

void IOConsole::WriteLine(String ^ str)
{
	Console::WriteLine(str);
}

String ^ IOConsole::Read()
{
	return Console::ReadLine();
}
