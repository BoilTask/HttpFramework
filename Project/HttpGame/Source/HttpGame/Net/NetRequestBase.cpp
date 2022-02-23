
#include "NetRequestBase.h"

#include "MessageManager.h"

void NetRequestBase::Send()
{
	UMessageManager::GetInstance().MessageSend(*this);
}

void NetRequestBase::Send(FString const& ServerUrl)
{
	UMessageManager::GetInstance().MessageSend(ServerUrl, *this);
}

void NetRequestBase::Send(FNetMessageDelegate Delegate)
{
	UMessageManager::GetInstance().MessageSend(*this, Delegate);
}
