#include "NetLoadingManager.h"

void UNetLoadingManager::Init()
{
	IsNetLoading_ = false;
	NetPacketCount_ = 0;
	NetPacketElapse_ = 0.f;

	NetLoadingThreshold_ = 0.3f;
}

void UNetLoadingManager::Tick(float DeltaSeconds)
{
	if (IsNetLoading_)
	{
		if (NetPacketCount_ <= 0)
		{
			NetPacketElapse_ = 0.f;
			CloseLoading();
		}
	}
	else
	{
		if (NetPacketCount_ > 0)
		{
			if (NetPacketElapse_ > NetLoadingThreshold_)
			{
				ShowLoading();
			}
			else
			{
				NetPacketElapse_ += DeltaSeconds;
			}
		}
		else
		{
			NetPacketElapse_ = 0.f;
		}
	}
}

void UNetLoadingManager::OnSend()
{
	NetPacketCount_++;
}

void UNetLoadingManager::OnReceive()
{
	NetPacketCount_--;
}

void UNetLoadingManager::ShowLoading()
{
	IsNetLoading_ = true;

}

void UNetLoadingManager::CloseLoading()
{
	IsNetLoading_ = false;

}
