
#include "NetRequestPackage.h"

NetRequestPackage::NetRequestPackage()
{
	NetRequestPackage::Clear();
}

void NetRequestPackage::Clear()
{
}

void NetRequestPackage::SetHeader(ENetHeader Header)
{
	Header_ = Header;
}

ENetHeader NetRequestPackage::GetHeader() const
{
	return Header_;
}

void NetRequestPackage::SetMsg(NetRequestBase const& Msg)
{
	Msg_ = Msg.Create();
}

NetRequestBase* NetRequestPackage::GetMsg() const
{
	return Msg_;
}
