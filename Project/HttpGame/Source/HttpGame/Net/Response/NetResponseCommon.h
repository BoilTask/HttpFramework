//Exported by Tool, please don't edit this file directly.

#pragma once

#include "NetDef.h"


class NetResponseCommonStatus;
class NetResponseCommonEntity;
class NetResponseCommonStatusMessage;

class NetResponseCommonStatus
{
public:
	NetResponseCommonStatus() = default;
	~NetResponseCommonStatus() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	int32 code() const;
	int64 time() const;

private:
	int32 code_;
	int64 time_;
};

class NetResponseCommonEntity
{
public:
	NetResponseCommonEntity() = default;
	~NetResponseCommonEntity() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);
};

class NetResponseCommonStatusMessage
{
public:
	NetResponseCommonStatusMessage() = default;
	~NetResponseCommonStatusMessage() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	bool has_status() const;
	NetResponseCommonStatus& status();
	bool has_entity() const;
	NetResponseCommonEntity& entity();

private:
	TSharedPtr<NetResponseCommonStatus> status_;
	TSharedPtr<NetResponseCommonEntity> entity_;
};
