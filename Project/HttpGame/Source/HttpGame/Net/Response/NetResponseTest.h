//Exported by Tool, please don't edit this file directly.

#pragma once

#include "NetDef.h"

#include "NetResponseCommon.h"
#include "NetResponseServer.h"

class NetResponseTestTest;
class NetResponseTestLogin;
class NetResponseTestLogout;

class NetResponseTestTest
{
public:
	NetResponseTestTest() = default;
	~NetResponseTestTest() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	bool bool_test() const;
	int32 int32_test() const;
	int64 int64_test() const;
	double float_test() const;
	FString const& string_test() const;
	TArray<int32> const& listint32_test() const;
	int32 listint32_test(int32 Index) const;
	int32 listint32_test_size() const;
	TArray<bool> const& vector_bool_test() const;
	bool vector_bool_test(int32 Index) const;
	int32 vector_bool_test_size() const;
	TArray<int32> const& vector_int32_test() const;
	int32 vector_int32_test(int32 Index) const;
	int32 vector_int32_test_size() const;
	TArray<int64> const& vector_int64_test() const;
	int64 vector_int64_test(int32 Index) const;
	int32 vector_int64_test_size() const;
	TArray<double> const& vector_float_test() const;
	double vector_float_test(int32 Index) const;
	int32 vector_float_test_size() const;
	TArray<FString> const& vector_string_test() const;
	FString const& vector_string_test(int32 Index) const;
	int32 vector_string_test_size() const;
	bool has_Login_test() const;
	NetResponseTestLogin& Login_test();
	TArray<TSharedPtr<NetResponseTestLogin>> const& vector_Login_test() const;
	NetResponseTestLogin const& vector_Login_test(int32 Index) const;
	int32 vector_Login_test_size() const;

private:
	bool bool_test_;
	int32 int32_test_;
	int64 int64_test_;
	double float_test_;
	FString string_test_;
	TArray<int32> listint32_test_;
	TArray<bool> vector_bool_test_;
	TArray<int32> vector_int32_test_;
	TArray<int64> vector_int64_test_;
	TArray<double> vector_float_test_;
	TArray<FString> vector_string_test_;
	TSharedPtr<NetResponseTestLogin> Login_test_;
	TArray<TSharedPtr<NetResponseTestLogin>> vector_Login_test_;
};

class NetResponseTestLogin
{
public:
	NetResponseTestLogin() = default;
	~NetResponseTestLogin() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	int32 playerId() const;
	FString const& token() const;
	bool has_user() const;
	NetResponseTestTest& user();

private:
	int32 playerId_;
	FString token_;
	TSharedPtr<NetResponseTestTest> user_;
};

class NetResponseTestLogout
{
public:
	NetResponseTestLogout() = default;
	~NetResponseTestLogout() = default;
	void Clear();
	bool ParseData(TSharedPtr<FJsonObject> const& Data);
	bool ParseData(TSharedPtr<FJsonObject> const* Data);

public:
	int32 playerId() const;
	FString const& token() const;
	bool testbool() const;
	double testfloat() const;
	bool has_testData() const;
	NetResponseTestLogin& testData();
	bool has_status() const;
	NetResponseCommonStatus& status();
	bool has_server() const;
	NetResponseServerLogin& server();

private:
	int32 playerId_;
	FString token_;
	bool testbool_;
	double testfloat_;
	TSharedPtr<NetResponseTestLogin> testData_;
	TSharedPtr<NetResponseCommonStatus> status_;
	TSharedPtr<NetResponseServerLogin> server_;
};
