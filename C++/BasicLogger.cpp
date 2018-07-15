#include "BasicLogger.h"
#include <iostream>

BasicLogger::BasicLogger(void)
{

}

BasicLogger::~BasicLogger(void)
{

}

void BasicLogger::WriteToConsole(std::string output)
{
	printf(output.c_str());
}

void BasicLogger::WriteToConsole(char* output)
{
	printf(output);
}
