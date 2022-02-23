
#include "MessageManager.h"

#include "MessageDispatcher.h"

#include "HttpModule.h"
#include "NetDef.h"
#include "NetLoadingManager.h"
#include "NetPacketFactory.h"
#include "NetResponseCommon.h"
#include "SubsystemDef.h"

UMessageManager::UMessageManager()
{
	Clear();
}

UMessageManager::~UMessageManager()
{

}

UMessageManager* UMessageManager::GetInstancePtr()
{
	return (SUBSYSTEM_GET_INS(MessageManager));
}

UMessageManager& UMessageManager::GetInstance()
{
	return *GetInstancePtr();
}

void UMessageManager::Clear()
{
	ServerUrl_ = "";
}

void UMessageManager::Initialize(FSubsystemCollectionBase& Collection)
{
	EnableTick_ = false;
	
	NetErrorCount_ = 0;
	
	NetLoadingManager_ = NewObject<UNetLoadingManager>();
	if(NetLoadingManager_)
	{
		NetLoadingManager_->Init();
	}
}

bool UMessageManager::IsTickable() const
{
	return EnableTick_ && !IsTemplate();
}

TStatId UMessageManager::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMessageManager, STATGROUP_Tickables);
}

void UMessageManager::Tick(float DeltaTime)
{
	if (NetLoadingManager_)
	{
		NetLoadingManager_->Tick(DeltaTime);
	}
}

void UMessageManager::SetServerUrl(FString const& Url)
{
	ServerUrl_ = Url;

	UE_LOG(LogTemp, Warning, TEXT("UMessageManager::SetServerUrl: %s"), *Url);
}

int32 UMessageManager::MessageSend(NetRequestBase& Msg)
{
	if (Msg.Server == "")
	{
		return MessageSend(ServerUrl_, Msg);
	}
	else
	{
		return MessageSend(Msg.Server, Msg);
	}
}

int32 UMessageManager::MessageSend(FString const& ServerUrl, NetRequestBase& Msg)
{
	NetRequestPackage* RequestData = GetEmptyRequestData();
	if(nullptr == RequestData)
	{
		UE_LOG(LogMemory, Error, TEXT("GetEmptyRequestData Error!"));
		return -1;
	}
	
	if (NetLoadingManager_)
	{
		NetLoadingManager_->OnSend();
	}

#ifdef NET_DEBUG
	UE_LOG(LogMemory, Warning, TEXT("MessageSend Request Id...%d"), RequestData->GetRequestId());
#endif
	
	const FString Url = ServerUrl + Msg.Url;
#ifdef NET_DEBUG
	UE_LOG(LogMemory, Warning, TEXT("[%s]%s"), *FString::FromInt(Msg.Header), *Url);
#endif

	RequestData->SetHeader(Msg.Header);
	RequestData->SetMsg(Msg);
	
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpReq = FHttpModule::Get().CreateRequest();

	HttpReq->SetHeader(TEXT("Request"), FString::FromInt(RequestData->GetRequestId()));

	auto Data = RequestData->GetMsg();
	if (nullptr == Data)
	{
		UE_LOG(LogMemory, Error, TEXT("RequestData Msg Error!"));
		return -1;
	}
	
	switch (Msg.Method)
	{
	case ENetMethod_GET:
		HttpReq->SetURL(Url + "?" + Data->ParseStr());
		HttpReq->SetVerb(TEXT("GET"));
		break;
	case ENetMethod_POST:
		HttpReq->SetURL(Url);
		HttpReq->SetVerb(TEXT("POST"));
		HttpReq->AppendToHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
		HttpReq->SetContentAsString(Data->ParseStr());
		break;
	}

	HttpReq->OnProcessRequestComplete().BindUObject(this, &UMessageManager::OnMessageReceive);

#ifdef NET_DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Content: %s"), *Data->ParseStr());
#endif
	
	HttpReq->ProcessRequest();

	return RequestData->GetRequestId();
}

int32 UMessageManager::MessageSend(NetRequestBase& Msg, FNetMessageDelegate Delegate)
{
	const int32 RequestId = MessageSend(Msg);
	if (RequestId >= 0)
	{
		auto const& It = DelegateMap_.Find(RequestId);
		if (It)
		{
			*It = Delegate;
		}
		else
		{
			DelegateMap_.Emplace(RequestId, Delegate);
		}
	}
	return RequestId;
}

void UMessageManager::OnMessageReceive(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
{
	if (NetLoadingManager_)
	{
		NetLoadingManager_->OnReceive();
	}

	const FString RequestStr = Request->GetHeader("Request");
	UE_LOG(LogMemory, Warning, TEXT("OnMessageReceive Request Id...%s"), *RequestStr);

	const int32 RequestId = FCString::Atoi(*RequestStr);

	NetRequestPackage* RequestData = GetRequestData(RequestId);
	if (nullptr == RequestData)
	{
		UE_LOG(LogMemory, Error, TEXT("GetRequestData Error...%s"), *RequestStr);
		return;
	}

	if (bSucceeded)
	{
		NetErrorCount_ = 0;
	}
	else
	{
		NetErrorCount_++;

		ShowNetError(NetErrorCount_ <= 3 ? ENetErrorType_NetError : ENetErrorType_NetErrorExit);
	}

	DispatchMessage(bSucceeded ,*RequestData, Response);

	RecycleRequestData(RequestData);
}

void UMessageManager::DispatchMessage(bool bSucceeded, NetRequestPackage& RequestData, FHttpResponsePtr& Response)
{
	if (nullptr == RequestData.GetMsg())
	{
		UE_LOG(LogMemory, Error, TEXT("RequestData Msg Error...%d"), RequestData.GetRequestId());
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;

	if (!bSucceeded)
	{
		UMessageDispatcher::GetInstance().DispatchMessage(bSucceeded, *RequestData.GetMsg(), JsonObject);
		return;
	}
	
	const FString Result = Response->GetContentAsString();

#ifdef NET_DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Json: %s"), *Result);
#endif

	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Result);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		UE_LOG(LogTemp, Error, TEXT("Json: %s"), *Result);
		return;
	}

	int32 NetCode = -1;
	NetResponseCommonStatusMessage& StateData = NetPacketFactory<NetResponseCommonStatusMessage>::Get();
	if (StateData.ParseData(JsonObject))
	{
		if (StateData.has_status())
		{
			NetCode = StateData.status().code();
		}
	}

	UMessageDispatcher::GetInstance().DispatchMessage(bSucceeded, *RequestData.GetMsg(), JsonObject);

	auto const& It = DelegateMap_.Find(RequestData.GetRequestId());
	if (It && It->IsBound())
	{
		It->Execute(NetCode);
		It->Unbind();
	}
}

void UMessageManager::HandleCloseNetError()
{
	CloseNetError();
}

void UMessageManager::ShowNetError(ENetErrorType ErrorType)
{
}

void UMessageManager::CloseNetError()
{
}

NetRequestPackage* UMessageManager::GetEmptyRequestData()
{
	return RequestData_.Spawn();
}

NetRequestPackage* UMessageManager::GetRequestData(int32 RequestId)
{
	return RequestData_.Get(RequestId);
}

void UMessageManager::RecycleRequestData(NetRequestPackage* Data)
{
	RequestData_.Recycle(Data);
}
