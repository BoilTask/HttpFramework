//Exported by Tool, please don't edit this file directly.

#include "NetResponseCommon.h"
#include "GameParser.h"

void NetResponseCommonStatus::Clear()
{
	code_ = 0;
	time_ = 0;
}

bool NetResponseCommonStatus::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseCommonStatus::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	(*Data)->TryGetNumberField("code", code_);

	(*Data)->TryGetNumberField("time", time_);

	return true;
}

int32 NetResponseCommonStatus::code() const
{
   return code_;
}

int64 NetResponseCommonStatus::time() const
{
   return time_;
}

void NetResponseCommonEntity::Clear()
{
}

bool NetResponseCommonEntity::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseCommonEntity::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	return true;
}

void NetResponseCommonStatusMessage::Clear()
{
	status_.Reset();
	entity_.Reset();
}

bool NetResponseCommonStatusMessage::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseCommonStatusMessage::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	const TSharedPtr<FJsonObject>* status_Data;
	if ((*Data)->TryGetObjectField("status", status_Data))
	{
	   if (!status_)
	   {
	      status_ = MakeShareable(new NetResponseCommonStatus());
	   }
	   status_->ParseData(status_Data);
	}

	const TSharedPtr<FJsonObject>* entity_Data;
	if ((*Data)->TryGetObjectField("entity", entity_Data))
	{
	   if (!entity_)
	   {
	      entity_ = MakeShareable(new NetResponseCommonEntity());
	   }
	   entity_->ParseData(entity_Data);
	}

	return true;
}

bool NetResponseCommonStatusMessage::has_status() const
{
   return status_.IsValid();
}

NetResponseCommonStatus& NetResponseCommonStatusMessage::status()
{
	if (!status_.IsValid())
	{
		status_ = MakeShareable(new NetResponseCommonStatus());
	}
	return *status_;
}

bool NetResponseCommonStatusMessage::has_entity() const
{
   return entity_.IsValid();
}

NetResponseCommonEntity& NetResponseCommonStatusMessage::entity()
{
	if (!entity_.IsValid())
	{
		entity_ = MakeShareable(new NetResponseCommonEntity());
	}
	return *entity_;
}
