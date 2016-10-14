#pragma once

using namespace System;

ref class IOConsole
{
public:
	IOConsole();

	static void Write(String ^ str);
	static void WriteLine(String ^ str);
	static String ^ Read();
};

