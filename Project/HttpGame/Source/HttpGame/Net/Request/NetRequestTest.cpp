//Exported by Tool, please don't edit this file directly.

#include "NetRequestTest.h"
#include "GameParser.h"

NetRequestTestTest::NetRequestTestTest()
	: bool_test_(false)
	, has_bool_test_(false)
	, int32_test_(0)
	, has_int32_test_(false)
	, int64_test_(0)
	, has_int64_test_(false)
	, float_test_(0.f)
	, has_float_test_(false)
	, has_string_test_(false)
{
	Header = ENetHeader_TestTest;
	Method = ENetMethod_POST;
	Server = "";
	Url = "/test/test";
}

NetRequestTestTest* NetRequestTestTest::Cast(NetRequestBase& Data)
{
	if (Data.Header != ENetHeader_TestTest)
	{
		return nullptr;
	}
	return static_cast<NetRequestTestTest*>(&Data);
}

NetRequestBase* NetRequestTestTest::Create() const
{
	const auto Data = new NetRequestTestTest();
	*Data = *this;
	return Data;
}

void NetRequestTestTest::Clear()
{
	bool_test_ = false;
	has_bool_test_ = false;
	int32_test_ = 0;
	has_int32_test_ = false;
	int64_test_ = 0;
	has_int64_test_ = false;
	float_test_ = 0.f;
	has_float_test_ = false;
	string_test_.Empty();
	has_string_test_ = false;
	vector_bool_test_.Empty();
	vector_int32_test_.Empty();
	vector_int64_test_.Empty();
	vector_float_test_.Empty();
	vector_string_test_.Empty();
}

FString NetRequestTestTest::ParseStr()
{
	DataString.Empty();
	bool IsFirst = true;
	if (has_bool_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("bool_test=");
		DataString.AppendInt(bool_test_?1:0);
	}
	if (has_int32_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("int32_test=");
		DataString.AppendInt(int32_test_);
	}
	if (has_int64_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("int64_test=");
		DataString.AppendInt(int64_test_);
	}
	if (has_float_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("float_test=");
		DataString.Append(FString::SanitizeFloat(float_test_));
	}
	if (has_string_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("string_test=");
		DataString.Append(string_test_);
	}
	if (has_vector_bool_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("vector_bool_test=");
		DataString.Append(GameParser::GetConvertListBool(vector_bool_test_));
	}
	if (has_vector_int32_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("vector_int32_test=");
		DataString.Append(GameParser::GetConvertListInt32(vector_int32_test_));
	}
	if (has_vector_int64_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("vector_int64_test=");
		DataString.Append(GameParser::GetConvertListInt64(vector_int64_test_));
	}
	if (has_vector_float_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("vector_float_test=");
		DataString.Append(GameParser::GetConvertListFloat(vector_float_test_));
	}
	if (has_vector_string_test())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		DataString.Append("vector_string_test=");
		DataString.Append(GameParser::GetConvertListString(vector_string_test_));
	}
	return DataString;
}

bool NetRequestTestTest::bool_test() const
{
	return bool_test_;
}

void NetRequestTestTest::set_bool_test(bool const& bool_test)
{
	has_bool_test_ = true;
	bool_test_ = bool_test;
}

bool NetRequestTestTest::has_bool_test() const
{
	return has_bool_test_;
}

int32 NetRequestTestTest::int32_test() const
{
   return int32_test_;
}

void NetRequestTestTest::set_int32_test(int32 const& int32_test)
{
	has_int32_test_ = true;
	int32_test_ = int32_test;
}

bool NetRequestTestTest::has_int32_test() const
{
   return has_int32_test_;
}

int64 NetRequestTestTest::int64_test() const
{
   return int64_test_;
}

void NetRequestTestTest::set_int64_test(int64 const& int64_test)
{
	has_int64_test_ = true;
	int64_test_ = int64_test;
}

bool NetRequestTestTest::has_int64_test() const
{
   return has_int64_test_;
}

float NetRequestTestTest::float_test() const
{
	return float_test_;
}

void NetRequestTestTest::set_float_test(float const& float_test)
{
	has_float_test_ = true;
	float_test_ = float_test;
}

bool NetRequestTestTest::has_float_test() const
{
   return has_float_test_;
}

FString const& NetRequestTestTest::string_test() const
{
   return string_test_;
}

void NetRequestTestTest::set_string_test(FString const& string_test)
{
	has_string_test_ = true;
	string_test_ = string_test;
}

bool NetRequestTestTest::has_string_test() const
{
   return has_string_test_;
}

TArray<bool> const& NetRequestTestTest::vector_bool_test() const
{
   return vector_bool_test_;
}

bool NetRequestTestTest::vector_bool_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_bool_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetRequestTestTest::vector_bool_test Out of Range!"));
   }
   return vector_bool_test_[Index];
}

int32 NetRequestTestTest::vector_bool_test_size() const
{
   return vector_bool_test_.Num();
}

void NetRequestTestTest::set_vector_bool_test(TArray<bool> const& vector_bool_test)
{
	vector_bool_test_ = vector_bool_test;
}

void NetRequestTestTest::add_vector_bool_test(bool const& vector_bool_test)
{
	vector_bool_test_.Emplace(vector_bool_test);
}

bool NetRequestTestTest::has_vector_bool_test() const
{
   return vector_bool_test_size() > 0;
}

TArray<int32> const& NetRequestTestTest::vector_int32_test() const
{
   return vector_int32_test_;
}

int32 NetRequestTestTest::vector_int32_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_int32_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetRequestTestTest::vector_int32_test Out of Range!"));
   }
   return vector_int32_test_[Index];
}

int32 NetRequestTestTest::vector_int32_test_size() const
{
   return vector_int32_test_.Num();
}

void NetRequestTestTest::set_vector_int32_test(TArray<int32> const& vector_int32_test)
{
	vector_int32_test_ = vector_int32_test;
}

void NetRequestTestTest::add_vector_int32_test(int32 const& vector_int32_test)
{
	vector_int32_test_.Emplace(vector_int32_test);
}

bool NetRequestTestTest::has_vector_int32_test() const
{
   return vector_int32_test_size() > 0;
}

TArray<int64> const& NetRequestTestTest::vector_int64_test() const
{
   return vector_int64_test_;
}

int64 NetRequestTestTest::vector_int64_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_int64_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetRequestTestTest::vector_int64_test Out of Range!"));
   }
   return vector_int64_test_[Index];
}

int32 NetRequestTestTest::vector_int64_test_size() const
{
   return vector_int64_test_.Num();
}

void NetRequestTestTest::set_vector_int64_test(TArray<int64> const& vector_int64_test)
{
	vector_int64_test_ = vector_int64_test;
}

void NetRequestTestTest::add_vector_int64_test(int64 const& vector_int64_test)
{
	vector_int64_test_.Emplace(vector_int64_test);
}

bool NetRequestTestTest::has_vector_int64_test() const
{
   return vector_int64_test_size() > 0;
}

TArray<float> const& NetRequestTestTest::vector_float_test() const
{
   return vector_float_test_;
}

float NetRequestTestTest::vector_float_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_float_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetRequestTestTest::vector_float_test Out of Range!"));
   }
   return vector_float_test_[Index];
}

int32 NetRequestTestTest::vector_float_test_size() const
{
   return vector_float_test_.Num();
}

void NetRequestTestTest::set_vector_float_test(TArray<float> const& vector_float_test)
{
	vector_float_test_ = vector_float_test;
}

void NetRequestTestTest::add_vector_float_test(float const& vector_float_test)
{
	vector_float_test_.Emplace(vector_float_test);
}

bool NetRequestTestTest::has_vector_float_test() const
{
   return vector_float_test_size() > 0;
}

TArray<FString> const& NetRequestTestTest::vector_string_test() const
{
   return vector_string_test_;
}

FString const& NetRequestTestTest::vector_string_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_string_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetRequestTestTest::vector_string_test Out of Range!"));
   }
   return vector_string_test_[Index];
}

int32 NetRequestTestTest::vector_string_test_size() const
{
   return vector_string_test_.Num();
}

void NetRequestTestTest::set_vector_string_test(TArray<FString> const& vector_string_test)
{
	vector_string_test_ = vector_string_test;
}

void NetRequestTestTest::add_vector_string_test(FString const& vector_string_test)
{
	vector_string_test_.Emplace(vector_string_test);
}

bool NetRequestTestTest::has_vector_string_test() const
{
   return vector_string_test_size() > 0;
}

NetRequestTestLogin::NetRequestTestLogin()
	: has_username_(false)
	, has_password_(false)
{
	Header = ENetHeader_TestLogin;
	Method = ENetMethod_POST;
	Server = "http://test.test.com";
	Url = "/api/login";
}

NetRequestTestLogin* NetRequestTestLogin::Cast(NetRequestBase& Data)
{
	if (Data.Header != ENetHeader_TestLogin)
	{
		return nullptr;
	}
	return static_cast<NetRequestTestLogin*>(&Data);
}

NetRequestBase* NetRequestTestLogin::Create() const
{
	const auto Data = new NetRequestTestLogin();
	*Data = *this;
	return Data;
}

void NetRequestTestLogin::Clear()
{
	username_.Empty();
	has_username_ = false;
	password_.Empty();
	has_password_ = false;
}

FString NetRequestTestLogin::ParseStr()
{
	DataString.Empty();
	bool IsFirst = true;
	if (has_username())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		else
		{
			IsFirst = false;
		}
		DataString.Append("username=");
		DataString.Append(username_);
	}
	if (has_password())
	{
		if (!IsFirst)
		{
			DataString.Append("&");
		}
		DataString.Append("password=");
		DataString.Append(password_);
	}
	return DataString;
}

FString const& NetRequestTestLogin::username() const
{
   return username_;
}

void NetRequestTestLogin::set_username(FString const& username)
{
	has_username_ = true;
	username_ = username;
}

bool NetRequestTestLogin::has_username() const
{
   return has_username_;
}

FString const& NetRequestTestLogin::password() const
{
   return password_;
}

void NetRequestTestLogin::set_password(FString const& password)
{
	has_password_ = true;
	password_ = password;
}

bool NetRequestTestLogin::has_password() const
{
   return has_password_;
}

NetRequestTestLogout::NetRequestTestLogout()
{
	Header = ENetHeader_TestLogout;
	Method = ENetMethod_GET;
	Server = "";
	Url = "/api/logout";
}

NetRequestTestLogout* NetRequestTestLogout::Cast(NetRequestBase& Data)
{
	if (Data.Header != ENetHeader_TestLogout)
	{
		return nullptr;
	}
	return static_cast<NetRequestTestLogout*>(&Data);
}

NetRequestBase* NetRequestTestLogout::Create() const
{
	const auto Data = new NetRequestTestLogout();
	*Data = *this;
	return Data;
}

void NetRequestTestLogout::Clear()
{
}

FString NetRequestTestLogout::ParseStr()
{
	DataString.Empty();
	return DataString;
}
