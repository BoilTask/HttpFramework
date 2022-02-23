#pragma once

#include "NetDef.h"
#include "TypeDef.h"

class NetRequestBase
{
public:
	NetRequestBase() = default;
	virtual ~NetRequestBase() = default;


	ENetHeader Header;
	ENetMethod Method;
	FString Server;
	FString Url;

	FString DataString;

	virtual void Clear() = 0;
	virtual FString ParseStr() = 0;
	virtual NetRequestBase* Create() const = 0;

	void Send();
	void Send(FString const& ServerUrl);
	void Send(FNetMessageDelegate Delegate);
};
