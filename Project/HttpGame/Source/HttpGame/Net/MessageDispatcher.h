#pragma once

#include "NetDef.h"

#include "MessageDispatcher.generated.h"

UCLASS()
class UMessageDispatcher : public UObject
{
	GENERATED_BODY()

public:
	UMessageDispatcher();
	~UMessageDispatcher();

	UFUNCTION(BlueprintCallable)
		static UMessageDispatcher* GetInstancePtr();
	static UMessageDispatcher& GetInstance();

private:
	static UMessageDispatcher* S_UMessageDispatcher_;

public:
	void DispatchMessage(bool bSucceeded, NetRequestData& RequestData, NetResponseData& ResponseData);

private:
	bool IsDispatchError(ENetHeader Header);
};
