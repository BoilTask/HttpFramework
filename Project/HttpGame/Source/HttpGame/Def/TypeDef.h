#pragma once

#include "TypeDef.generated.h"

USTRUCT(BlueprintType)
struct FGameDate
{
	GENERATED_BODY()

		void Clear()
	{
		Year = 0;
		Month = 0;
		Day = 0;
	}

	UPROPERTY(BlueprintReadWrite)
		int32 Year;
	UPROPERTY(BlueprintReadWrite)
		int32 Month;
	UPROPERTY(BlueprintReadWrite)
		int32 Day;
};
