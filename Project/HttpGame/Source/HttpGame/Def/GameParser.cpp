
#include "GameParser.h"

void GameParser::ParseListBool(FString const& ListStr, TArray<bool>& List)
{
	List.Empty();

	TArray<FString> StrList;
	ListStr.ParseIntoArray(StrList, TEXT(","), false);

	for (auto const& Str : StrList)
	{
		List.Emplace(FCString::Atoi(*Str) > 0);
	}
}

void GameParser::ConvertListBool(TArray<bool> const& List, FString& ListStr)
{
	ListStr.Empty();

	for (int32 i = 0; i < List.Num(); i++)
	{
		auto const& Item = List[i];
		if (i > 0)
		{
			ListStr.AppendChar(',');
		}
		ListStr.AppendChar(Item ? '1' : '0');
	}
}

FString GameParser::GetConvertListBool(TArray<bool> const& List)
{
	FString Str;
	ConvertListBool(List, Str);
	return Str;
}

void GameParser::ParseListInt32(FString const& ListStr, TArray<int32>& List)
{
	List.Empty();

	TArray<FString> StrList;
	ListStr.ParseIntoArray(StrList, TEXT(","), false);

	for (auto const& Str : StrList)
	{
		List.Emplace(FCString::Atoi(*Str));
	}
}

void GameParser::ConvertListInt32(TArray<int32> const& List, FString& ListStr)
{
	ListStr.Empty();

	for (int32 i = 0; i < List.Num(); i++)
	{
		auto const& Item = List[i];
		if (i > 0)
		{
			ListStr.AppendChar(',');
		}
		ListStr.AppendInt(Item);
	}
}

FString GameParser::GetConvertListInt32(TArray<int32> const& List)
{
	FString Str;
	ConvertListInt32(List, Str);
	return Str;
}

void GameParser::ParseListInt64(FString const& ListStr, TArray<int64>& List)
{
	List.Empty();

	TArray<FString> StrList;
	ListStr.ParseIntoArray(StrList, TEXT(","), false);

	for (auto const& Str : StrList)
	{
		List.Emplace(FCString::Atoi64(*Str));
	}
}

void GameParser::ConvertListInt64(TArray<int64> const& List, FString& ListStr)
{
	ListStr.Empty();

	for (int32 i = 0; i < List.Num(); i++)
	{
		auto const& Item = List[i];
		if (i > 0)
		{
			ListStr.AppendChar(',');
		}
		ListStr.AppendInt(Item);
	}
}

FString GameParser::GetConvertListInt64(TArray<int64> const& List)
{
	FString Str;
	ConvertListInt64(List, Str);
	return Str;
}

void GameParser::ParseListFloat(FString const& ListStr, TArray<float>& List)
{
	List.Empty();

	TArray<FString> StrList;
	ListStr.ParseIntoArray(StrList, TEXT(","), false);

	for (auto const& Str : StrList)
	{
		List.Emplace(FCString::Atof(*Str));
	}
}

void GameParser::ConvertListFloat(TArray<float> const& List, FString& ListStr)
{
	ListStr.Empty();

	for (int32 i = 0; i < List.Num(); i++)
	{
		auto const& Item = List[i];
		if (i > 0)
		{
			ListStr.AppendChar(',');
		}
		ListStr.Append(FString::SanitizeFloat(Item));
	}
}

FString GameParser::GetConvertListFloat(TArray<float> const& List)
{
	FString Str;
	ConvertListFloat(List, Str);
	return Str;
}

void GameParser::ParseListString(FString const& ListStr, TArray<FString>& List)
{
	List.Empty();

	TArray<FString> StrList;
	ListStr.ParseIntoArray(StrList, TEXT(","), false);

	for (auto const& Str : StrList)
	{
		List.Emplace(Str);
	}
}

void GameParser::ConvertListString(TArray<FString> const& List, FString& ListStr)
{
	ListStr.Empty();


}

FString GameParser::GetConvertListString(TArray<FString> const& List)
{
	FString Str;
	ConvertListString(List, Str);
	return Str;
}

FGameDate GameParser::ParseGameDate(FString const& Str)
{
	FString LeftStr;
	FString RightStr;
	FGameDate Date;
	Str.Split("-", &LeftStr, &RightStr);
	Date.Year = FCString::Atoi(*LeftStr);
	RightStr.Split("-", &LeftStr, &RightStr);
	Date.Month = FCString::Atoi(*LeftStr);
	RightStr.Split("-", &LeftStr, &RightStr);
	Date.Day = FCString::Atoi(*LeftStr);
	return Date;
}

FString GameParser::ConvertGameDate(int32 Year, int32 Month, int32 Day)
{
	FString Res = "";
	Res += FString::FromInt(Year);
	Res += "-";
	if (Month < 10)
	{
		Res += "0";
	}
	Res += FString::FromInt(Month);
	Res += "-";
	if (Day < 10)
	{
		Res += "0";
	}
	Res += FString::FromInt(Day);
	return Res;
}

FString GameParser::ConvertGameDate(FGameDate const& Date)
{
	return ConvertGameDate(Date.Year, Date.Month, Date.Day);
}
