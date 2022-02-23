#pragma once

#include "TypeDef.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "NetDef.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNetResponse, Log, All);

DECLARE_DYNAMIC_DELEGATE_OneParam(FNetMessageDelegate, int32, Code);

class NetRequestBase;
using NetRequestData = NetRequestBase;
using NetResponseData = TSharedPtr<FJsonObject>;

UENUM(BlueprintType, Blueprintable)
enum ENetMethod
{
	ENetMethod_GET,
	ENetMethod_POST
};

//Don't edit the following content.NET_DEF_START
enum ENetHeader
{
	ENetHeader_None = 0,
	ENetHeader_TestTest,
	ENetHeader_TestLogin,
	ENetHeader_TestLogout,
	ENetHeader_Max
};
//Don't edit the above content.NET_DEF_END
