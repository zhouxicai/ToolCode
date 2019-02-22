#include <iostream>
#include "MessageHandler.h"
#include "TestHandler.h"

int main() {
	MessageHandler*	m_msgHandler;
	m_msgHandler = MsgHandlerFactory::getInstance()->create(1);
	MsgHandlerFactory::getInstance()->destroy(GZ_1, m_msgHandler);
}