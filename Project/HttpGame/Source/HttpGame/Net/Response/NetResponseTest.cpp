//Exported by Tool, please don't edit this file directly.

#include "NetResponseTest.h"
#include "GameParser.h"

void NetResponseTestTest::Clear()
{
	bool_test_ = false;
	int32_test_ = 0;
	int64_test_ = 0;
	float_test_ = 0.f;
	string_test_.Empty();
	listint32_test_.Empty();
	vector_bool_test_.Empty();
	vector_int32_test_.Empty();
	vector_int64_test_.Empty();
	vector_float_test_.Empty();
	vector_string_test_.Empty();
	Login_test_.Reset();
	vector_Login_test_.Empty();
}

bool NetResponseTestTest::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseTestTest::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	(*Data)->TryGetBoolField("bool_test", bool_test_);

	(*Data)->TryGetNumberField("int32_test", int32_test_);

	(*Data)->TryGetNumberField("int64_test", int64_test_);

	(*Data)->TryGetNumberField("float_test", float_test_);

	(*Data)->TryGetStringField("string_test", string_test_);

	FString listint32_test_str_;
	(*Data)->TryGetStringField("listint32_test", listint32_test_str_);
	GameParser::ParseListInt32(listint32_test_str_, listint32_test_);

	const TArray<TSharedPtr<FJsonValue>>* vector_bool_test_Data;
	if ((*Data)->TryGetArrayField("vector_bool_test", vector_bool_test_Data) && vector_bool_test_Data)
	{
		for (auto const & vector_bool_test_Item: *vector_bool_test_Data)
		{
			bool _Temp;
			(*vector_bool_test_Item).TryGetBool(_Temp);
			vector_bool_test_.Emplace(_Temp);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* vector_int32_test_Data;
	if ((*Data)->TryGetArrayField("vector_int32_test", vector_int32_test_Data) && vector_int32_test_Data)
	{
		for (auto const & vector_int32_test_Item: *vector_int32_test_Data)
		{
			int32 _Temp;
			(*vector_int32_test_Item).TryGetNumber(_Temp);
			vector_int32_test_.Emplace(_Temp);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* vector_int64_test_Data;
	if ((*Data)->TryGetArrayField("vector_int64_test", vector_int64_test_Data) && vector_int64_test_Data)
	{
		for (auto const & vector_int64_test_Item: *vector_int64_test_Data)
		{
			int64 _Temp;
			(*vector_int64_test_Item).TryGetNumber(_Temp);
			vector_int64_test_.Emplace(_Temp);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* vector_float_test_Data;
	if ((*Data)->TryGetArrayField("vector_float_test", vector_float_test_Data) && vector_float_test_Data)
	{
		for (auto const & vector_float_test_Item: *vector_float_test_Data)
		{
			double _Temp;
			(*vector_float_test_Item).TryGetNumber(_Temp);
			vector_float_test_.Emplace(_Temp);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* vector_string_test_Data;
	if ((*Data)->TryGetArrayField("vector_string_test", vector_string_test_Data) && vector_string_test_Data)
	{
		for (auto const & vector_string_test_Item: *vector_string_test_Data)
		{
			FString _Temp;
			(*vector_string_test_Item).TryGetString(_Temp);
			vector_string_test_.Emplace(_Temp);
		}
	}

	const TSharedPtr<FJsonObject>* Login_test_Data;
	if ((*Data)->TryGetObjectField("Login_test", Login_test_Data))
	{
	   if (!Login_test_)
	   {
	      Login_test_ = MakeShareable(new NetResponseTestLogin());
	   }
	   Login_test_->ParseData(Login_test_Data);
	}

	const TArray<TSharedPtr<FJsonValue>>* vector_Login_test_Data;
	if ((*Data)->TryGetArrayField("vector_Login_test", vector_Login_test_Data) && vector_Login_test_Data)
	{
		for (auto const & vector_Login_test_Item: *vector_Login_test_Data)
		{
			const TSharedPtr<FJsonObject>* _Temp;
			(*vector_Login_test_Item).TryGetObject(_Temp);
			TSharedPtr<NetResponseTestLogin> vector_Login_test_Ptr = MakeShareable(new NetResponseTestLogin());
			vector_Login_test_Ptr->ParseData(_Temp);
			vector_Login_test_.Emplace(vector_Login_test_Ptr);
		}
	}

	return true;
}

bool NetResponseTestTest::bool_test() const
{
   return bool_test_;
}

int32 NetResponseTestTest::int32_test() const
{
   return int32_test_;
}

int64 NetResponseTestTest::int64_test() const
{
   return int64_test_;
}

double NetResponseTestTest::float_test() const
{
   return float_test_;
}

FString const& NetResponseTestTest::string_test() const
{
   return string_test_;
}

TArray<int32> const& NetResponseTestTest::listint32_test() const
{
   return listint32_test_;
}

int32 NetResponseTestTest::listint32_test(int32 Index) const
{
   if (!(Index >= 0 && Index < listint32_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::listint32_test Out of Range!"));
   }
   return listint32_test_[Index];
}

int32 NetResponseTestTest::listint32_test_size() const
{
   return listint32_test_.Num();
}

TArray<bool> const& NetResponseTestTest::vector_bool_test() const
{
   return vector_bool_test_;
}

bool NetResponseTestTest::vector_bool_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_bool_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_bool_test Out of Range!"));
   }
   return vector_bool_test_[Index];
}

int32 NetResponseTestTest::vector_bool_test_size() const
{
   return vector_bool_test_.Num();
}

TArray<int32> const& NetResponseTestTest::vector_int32_test() const
{
   return vector_int32_test_;
}

int32 NetResponseTestTest::vector_int32_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_int32_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_int32_test Out of Range!"));
   }
   return vector_int32_test_[Index];
}

int32 NetResponseTestTest::vector_int32_test_size() const
{
   return vector_int32_test_.Num();
}

TArray<int64> const& NetResponseTestTest::vector_int64_test() const
{
   return vector_int64_test_;
}

int64 NetResponseTestTest::vector_int64_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_int64_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_int64_test Out of Range!"));
   }
   return vector_int64_test_[Index];
}

int32 NetResponseTestTest::vector_int64_test_size() const
{
   return vector_int64_test_.Num();
}

TArray<double> const& NetResponseTestTest::vector_float_test() const
{
   return vector_float_test_;
}

double NetResponseTestTest::vector_float_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_float_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_float_test Out of Range!"));
   }
   return vector_float_test_[Index];
}

int32 NetResponseTestTest::vector_float_test_size() const
{
   return vector_float_test_.Num();
}

TArray<FString> const& NetResponseTestTest::vector_string_test() const
{
   return vector_string_test_;
}

FString const& NetResponseTestTest::vector_string_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_string_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_string_test Out of Range!"));
   }
   return vector_string_test_[Index];
}

int32 NetResponseTestTest::vector_string_test_size() const
{
   return vector_string_test_.Num();
}

bool NetResponseTestTest::has_Login_test() const
{
   return Login_test_.IsValid();
}

NetResponseTestLogin& NetResponseTestTest::Login_test()
{
	if (!Login_test_.IsValid())
	{
		Login_test_ = MakeShareable(new NetResponseTestLogin());
	}
	return *Login_test_;
}

TArray<TSharedPtr<NetResponseTestLogin>> const& NetResponseTestTest::vector_Login_test() const
{
   return vector_Login_test_;
}

NetResponseTestLogin const& NetResponseTestTest::vector_Login_test(int32 Index) const
{
   if (!(Index >= 0 && Index < vector_Login_test_size()))
   {
      UE_LOG(LogNetResponse, Error, TEXT("NetResponseTestTest::vector_Login_test Out of Range!"));
   }
   return *vector_Login_test_[Index];
}

int32 NetResponseTestTest::vector_Login_test_size() const
{
   return vector_Login_test_.Num();
}

void NetResponseTestLogin::Clear()
{
	playerId_ = 0;
	token_.Empty();
	user_.Reset();
}

bool NetResponseTestLogin::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseTestLogin::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	(*Data)->TryGetNumberField("playerId", playerId_);

	(*Data)->TryGetStringField("token", token_);

	const TSharedPtr<FJsonObject>* user_Data;
	if ((*Data)->TryGetObjectField("user", user_Data))
	{
	   if (!user_)
	   {
	      user_ = MakeShareable(new NetResponseTestTest());
	   }
	   user_->ParseData(user_Data);
	}

	return true;
}

int32 NetResponseTestLogin::playerId() const
{
   return playerId_;
}

FString const& NetResponseTestLogin::token() const
{
   return token_;
}

bool NetResponseTestLogin::has_user() const
{
   return user_.IsValid();
}

NetResponseTestTest& NetResponseTestLogin::user()
{
	if (!user_.IsValid())
	{
		user_ = MakeShareable(new NetResponseTestTest());
	}
	return *user_;
}

void NetResponseTestLogout::Clear()
{
	playerId_ = 0;
	token_.Empty();
	testbool_ = false;
	testfloat_ = 0.f;
	testData_.Reset();
	status_.Reset();
	server_.Reset();
}

bool NetResponseTestLogout::ParseData(TSharedPtr<FJsonObject> const& Data)
{
	return ParseData(&Data);
}

bool NetResponseTestLogout::ParseData(TSharedPtr<FJsonObject> const* Data)
{
	Clear();

	if (nullptr == Data || !(*Data).IsValid())
	{
		return false;
	}

	(*Data)->TryGetNumberField("playerId", playerId_);

	(*Data)->TryGetStringField("token", token_);

	(*Data)->TryGetBoolField("testbool", testbool_);

	(*Data)->TryGetNumberField("testfloat", testfloat_);

	const TSharedPtr<FJsonObject>* testData_Data;
	if ((*Data)->TryGetObjectField("testData", testData_Data))
	{
	   if (!testData_)
	   {
	      testData_ = MakeShareable(new NetResponseTestLogin());
	   }
	   testData_->ParseData(testData_Data);
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

	const TSharedPtr<FJsonObject>* server_Data;
	if ((*Data)->TryGetObjectField("server", server_Data))
	{
	   if (!server_)
	   {
	      server_ = MakeShareable(new NetResponseServerLogin());
	   }
	   server_->ParseData(server_Data);
	}

	return true;
}

int32 NetResponseTestLogout::playerId() const
{
   return playerId_;
}

FString const& NetResponseTestLogout::token() const
{
   return token_;
}

bool NetResponseTestLogout::testbool() const
{
   return testbool_;
}

double NetResponseTestLogout::testfloat() const
{
   return testfloat_;
}

bool NetResponseTestLogout::has_testData() const
{
   return testData_.IsValid();
}

NetResponseTestLogin& NetResponseTestLogout::testData()
{
	if (!testData_.IsValid())
	{
		testData_ = MakeShareable(new NetResponseTestLogin());
	}
	return *testData_;
}

bool NetResponseTestLogout::has_status() const
{
   return status_.IsValid();
}

NetResponseCommonStatus& NetResponseTestLogout::status()
{
	if (!status_.IsValid())
	{
		status_ = MakeShareable(new NetResponseCommonStatus());
	}
	return *status_;
}

bool NetResponseTestLogout::has_server() const
{
   return server_.IsValid();
}

NetResponseServerLogin& NetResponseTestLogout::server()
{
	if (!server_.IsValid())
	{
		server_ = MakeShareable(new NetResponseServerLogin());
	}
	return *server_;
}
