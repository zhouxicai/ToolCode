#ifndef _AN_SHUN_HANDLER_H
#define _AN_SHUN_HANDLER_H

#include "MessageHandler.h"

#define GZ_1 1

class TestHandler : public MessageHandler
{
public:
	TestHandler();
	virtual ~TestHandler();

public:
	virtual bool init(int *desk);
	virtual void shutdown();


private:
	int			m_curPos;

};
DECLARE_GAME_HANDLER_CREATOR(GZ_1, TestHandler)

#endif