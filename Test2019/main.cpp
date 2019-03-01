#include <iostream>
#include "MessageHandler.h"
#include "TestHandler.h"
MessageHandler*	m_msgHandler;
bool _createRegister(int gameType)
{
	m_msgHandler = MsgHandlerFactory::getInstance()->create(gameType);
	if (!m_msgHandler)
	{
		return false;
	}
	return true;
}
void _destreRegister(int gameType)
{
	if (m_msgHandler)
	{
		MsgHandlerFactory::getInstance()->destroy(gameType, m_msgHandler);
		m_msgHandler = 0;
	}
}
int main() {
	_createRegister(GZ_1);
	_destreRegister(GZ_1);
}