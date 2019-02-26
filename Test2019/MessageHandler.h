#ifndef GameHandler_h
#define GameHandler_h
#include <list>
#include <map>

class MessageHandler
{
public:
	MessageHandler()
	{
		m_bLianZhuangFlag = false;
	}
	virtual bool			init() { return false; }
    virtual void			clear() {}

protected:
	int					m_userCount;
private:
	bool				m_bLianZhuangFlag;				


	 
};

class MsgHandlerCreator
{
public:
    virtual MessageHandler* create(void) = 0;
};

class MsgHandlerFactory
{
public:
    MsgHandlerFactory(void);
    ~MsgHandlerFactory(void);

    static MsgHandlerFactory* getInstance(void);

    MessageHandler* create(int gameType);
    void destroy(int gameType, MessageHandler *gameHandler);

    void registerCreator(int gameType, MsgHandlerCreator *creator);
    void unregisterCreator(int gameType);

private:
    std::map<int, MsgHandlerCreator*> mCreators;
    std::map<int, std::list<MessageHandler*> > mFreeHandlers;
};


#define DECLARE_GAME_HANDLER_CREATOR(gameType, className)                           \
class MsgHandlerCreator_##className : public MsgHandlerCreator                    \
{                                                                                   \
public:                                                                             \
    MsgHandlerCreator_##className(void)                                            \
    {                                                                               \
        MsgHandlerFactory::getInstance()->registerCreator(gameType,                \
            (MsgHandlerCreator*)this);                                             \
    }                                                                               \
    ~MsgHandlerCreator_##className(void)                                           \
    {                                                                               \
        MsgHandlerFactory::getInstance()->unregisterCreator(                       \
            gameType);                                                              \
    }                                                                               \
    MessageHandler* create(void)                                                    \
    {                                                                               \
        return new className();                                                     \
    }                                                                               \
};                                                                                  \
static MsgHandlerCreator_##className sGameHandlerCreator_##className;
#endif
