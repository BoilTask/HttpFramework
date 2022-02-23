
#pragma once

#include "NetDef.h"
#include "NetRequestBase.h"
#include "SimObjectPool.h"

class NetRequestPackage : public dida::SimObjectItem
{
public:
	NetRequestPackage();

public:
	virtual void Clear() override;
	DECLARE_OBJECT_POOL_ID(RequestId)

public:
	void SetHeader(ENetHeader Header);
	ENetHeader GetHeader() const;

	void SetMsg(NetRequestBase const& Msg);
	NetRequestBase* GetMsg() const;

private:
	ENetHeader Header_;
	NetRequestBase* Msg_;
};
