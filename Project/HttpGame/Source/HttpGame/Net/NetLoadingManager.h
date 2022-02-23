
#pragma once

#include "NetDef.h"

#include "NetLoadingManager.generated.h"

UCLASS()
class UNetLoadingManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();
	void Tick(float DeltaSeconds);

	void OnSend();
	void OnReceive();

private:
	void ShowLoading();
	void CloseLoading();

private:
	float NetLoadingThreshold_;
	bool IsNetLoading_;
	int32 NetPacketCount_;
	float NetPacketElapse_;
};
