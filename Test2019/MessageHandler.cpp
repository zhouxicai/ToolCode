#include "MessageHandler.h"


MsgHandlerFactory::MsgHandlerFactory(void)
{
}
MsgHandlerFactory::~MsgHandlerFactory(void)
{
}

MsgHandlerFactory* MsgHandlerFactory::getInstance(void)
{
    static MsgHandlerFactory sInstance;
    return &sInstance;
}

MessageHandler* MsgHandlerFactory::create(int gameType)
{
    std::map<int, std::list<MessageHandler*> >::iterator iHandlers = mFreeHandlers.find(gameType);
    if (iHandlers != mFreeHandlers.end())
    {
        if (iHandlers->second.size() > 0)
        {
            MessageHandler *handler = iHandlers->second.front();
            iHandlers->second.pop_front();
            return handler;
        }
    }

    std::map<int, MsgHandlerCreator*>::iterator iCreator = mCreators.find(gameType);
    if (iCreator != mCreators.end())
    {
        return iCreator->second->create();
    }
    return 0;
}
void MsgHandlerFactory::destroy(int gameType, MessageHandler *gameHandler)
{
    if (gameHandler)
    {
        gameHandler->clear();

        std::map<int, std::list<MessageHandler*> >::iterator iHandlers = mFreeHandlers.find(gameType);
        if (iHandlers != mFreeHandlers.end())
        {
            iHandlers->second.push_back(gameHandler);
        }
        else
        {
            std::list<MessageHandler*> handlers;
            handlers.push_back(gameHandler);
            mFreeHandlers[gameType] = handlers;
        }
    }
}

void MsgHandlerFactory::registerCreator(int gameType, MsgHandlerCreator *creator)
{
    if (creator)
    {
        mCreators[gameType] = creator;
    }
}
void MsgHandlerFactory::unregisterCreator(int gameType)
{
    mCreators.erase(gameType);
}

