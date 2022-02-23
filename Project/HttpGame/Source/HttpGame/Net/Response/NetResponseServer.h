//Exported by Tool, please don't edit this file directly.

#pragma once

#include "NetDef.h"

#include "NetResponseCommon.h"

class NetResponseServerLogin;

class NetResponseServerLogin
{
public:
	NetResponseServerLogin() = default;
	~NetResponseServerLogin() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	int32 id() const;
	FString const& name() const;
	FString const& url() const;

private:
	int32 id_;
	FString name_;
	FString url_;
};
