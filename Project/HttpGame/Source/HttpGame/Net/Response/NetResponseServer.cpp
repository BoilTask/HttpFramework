//Exported by Tool, please don't edit this file directly.

#include "NetResponseServer.h"
#include "GameParser.h"

void NetResponseServerLogin::Clear()
{
	id_ = 0;
	name_.Empty();
	url_.Empty();
}

bool NetResponseServerLogin::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseServerLogin::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	(*Data)->TryGetNumberField("id", id_);

	(*Data)->TryGetStringField("name", name_);

	(*Data)->TryGetStringField("url", url_);

	return true;
}

int32 NetResponseServerLogin::id() const
{
   return id_;
}

FString const& NetResponseServerLogin::name() const
{
   return name_;
}

FString const& NetResponseServerLogin::url() const
{
   return url_;
}
