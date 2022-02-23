
#include "MessageDispatcher.h"

#include "NetRequestBase.h"

UMessageDispatcher* UMessageDispatcher::S_UMessageDispatcher_ = nullptr;

UMessageDispatcher::UMessageDispatcher()
{
}

UMessageDispatcher::~UMessageDispatcher()
{

}

UMessageDispatcher* UMessageDispatcher::GetInstancePtr()
{
	if (S_UMessageDispatcher_ == nullptr)
	{
		S_UMessageDispatcher_ = NewObject<UMessageDispatcher>();
		S_UMessageDispatcher_->AddToRoot();
	}
	return S_UMessageDispatcher_;
}

UMessageDispatcher& UMessageDispatcher::GetInstance()
{
	return *GetInstancePtr();
}

void UMessageDispatcher::DispatchMessage(bool bSucceeded, NetRequestData& RequestData, NetResponseData& ResponseData)
{
	const ENetHeader Header = RequestData.Header;

	if(!bSucceeded && !IsDispatchError(Header))
	{
		return;
	}
	
	switch (Header)
	{
	case ENetHeader_None:

		break;
	default: ;
	}
}

bool UMessageDispatcher::IsDispatchError(ENetHeader Header)
{
	switch (Header)
	{
	case ENetHeader_None:
		return true;
	default: ;
	}
	return false;
}
