#pragma once

#include "DataDef.generated.h"

UENUM(BlueprintType, Blueprintable)
enum ENetErrorType
{
	ENetErrorType_NetError = 0,
	ENetErrorType_NetErrorExit = 1,
	ENetErrorType_LoginError = 2
};
