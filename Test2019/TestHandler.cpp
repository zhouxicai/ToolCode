#include "TestHandler.h"


TestHandler::TestHandler()
{
}

TestHandler::~TestHandler()
{
}

bool TestHandler::init(int *desk)
{
	if (NULL == desk)
	{
		return false;
	}

	shutdown();

	return true;
}

void TestHandler::shutdown()
{
	*this = TestHandler();	//Ç°¿½±´ÇåÁã
}
