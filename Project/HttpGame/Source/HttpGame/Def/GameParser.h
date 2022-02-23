#pragma once

#include "TypeDef.h"

class GameParser
{
public:
	static void ParseListBool(FString const& ListStr, TArray<bool>& List);
	static void ConvertListBool(TArray<bool> const& List, FString& ListStr);
	static FString GetConvertListBool(TArray<bool> const& List);

	static void ParseListInt32(FString const& ListStr, TArray<int32>& List);
	static void ConvertListInt32(TArray<int32> const& List, FString& ListStr);
	static FString GetConvertListInt32(TArray<int32> const& List);

	static void ParseListInt64(FString const& ListStr, TArray<int64>& List);
	static void ConvertListInt64(TArray<int64> const& List, FString& ListStr);
	static FString GetConvertListInt64(TArray<int64> const& List);

	static void ParseListFloat(FString const& ListStr, TArray<float>& List);
	static void ConvertListFloat(TArray<float> const& List, FString& ListStr);
	static FString GetConvertListFloat(TArray<float> const& List);

	//TODO
	static void ParseListString(FString const& ListStr, TArray<FString>& List);
	static void ConvertListString(TArray<FString> const& List, FString& ListStr);
	static FString GetConvertListString(TArray<FString> const& List);

	// 1999-01-01
	static FGameDate ParseGameDate(FString const& Str);
	static FString ConvertGameDate(int32 Year, int32 Month, int32 Day);
	static FString ConvertGameDate(FGameDate const& Date);
};
