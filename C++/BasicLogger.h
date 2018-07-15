#pragma once
#include <string>

class BasicLogger
{
public:

	static void WriteToConsole(std::string output);
	static void WriteToConsole(char* output);

private:

	BasicLogger(void);
	~BasicLogger(void);
};