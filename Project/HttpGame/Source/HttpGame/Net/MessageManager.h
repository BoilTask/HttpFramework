
#pragma once

#include "DataDef.h"
#include "NetDef.h"
#include "NetLoadingManager.h"
#include "NetRequestBase.h"
#include "NetRequestPackage.h"
#include "SimObjectPool.h"

#include "MessageManager.generated.h"

UCLASS()
class UMessageManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UMessageManager();
	virtual ~UMessageManager() override;

	UFUNCTION(BlueprintCallable)
		static UMessageManager* GetInstancePtr();
	static UMessageManager& GetInstance();

public:
	void Clear();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;

	void EnableTick() { EnableTick_ = true; }

	void SetServerUrl(FString const& Url);

	int32 MessageSend(NetRequestBase& Msg);
	int32 MessageSend(FString const& ServerUrl, NetRequestBase& Msg);
	int32 MessageSend(NetRequestBase& Msg, FNetMessageDelegate Delegate);
	
	void OnMessageReceive(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded);

	UFUNCTION(BlueprintCallable)
		void HandleCloseNetError();
	
	UFUNCTION(BlueprintCallable)
		void ShowNetError(ENetErrorType ErrorType);

private:
	void DispatchMessage(bool bSucceeded, NetRequestPackage& RequestData, FHttpResponsePtr& Response);
	void CloseNetError();

private:
	NetRequestPackage* GetEmptyRequestData();
	NetRequestPackage* GetRequestData(int32 RequestId);
	void RecycleRequestData(NetRequestPackage* Data);

private:
	dida::ExpandObjectPool<NetRequestPackage, 3> RequestData_;
	TMap<int32, FNetMessageDelegate> DelegateMap_;

private:
	bool EnableTick_;
	
	FString ServerUrl_;

	UPROPERTY()
		UNetLoadingManager* NetLoadingManager_;

	int32 NetErrorCount_;
};
