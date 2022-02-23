#pragma once

//Exported by Tool, please don't edit this file directly.

#include "NetRequestBase.h"

class NetRequestTestTest : public NetRequestBase
{
public:
	NetRequestTestTest();

	static NetRequestTestTest* Cast(NetRequestBase& Data);

	virtual NetRequestBase* Create() const override;

	virtual void Clear() override;

	virtual FString ParseStr() override;

public:
	bool bool_test() const;
	void set_bool_test(bool const& bool_test);
	bool has_bool_test() const;
	int32 int32_test() const;
	void set_int32_test(int32 const& int32_test);
	bool has_int32_test() const;
	int64 int64_test() const;
	void set_int64_test(int64 const& int64_test);
	bool has_int64_test() const;
	float float_test() const;
	void set_float_test(float const& float_test);
	bool has_float_test() const;
	FString const& string_test() const;
	void set_string_test(FString const& string_test);
	bool has_string_test() const;
	TArray<bool> const& vector_bool_test() const;
	bool vector_bool_test(int32 Index) const;
	int32 vector_bool_test_size() const;
	void add_vector_bool_test(bool const& vector_bool_test);
	void set_vector_bool_test(TArray<bool> const& vector_bool_test);
	bool has_vector_bool_test() const;
	TArray<int32> const& vector_int32_test() const;
	int32 vector_int32_test(int32 Index) const;
	int32 vector_int32_test_size() const;
	void add_vector_int32_test(int32 const& vector_int32_test);
	void set_vector_int32_test(TArray<int32> const& vector_int32_test);
	bool has_vector_int32_test() const;
	TArray<int64> const& vector_int64_test() const;
	int64 vector_int64_test(int32 Index) const;
	int32 vector_int64_test_size() const;
	void add_vector_int64_test(int64 const& vector_int64_test);
	void set_vector_int64_test(TArray<int64> const& vector_int64_test);
	bool has_vector_int64_test() const;
	TArray<float> const& vector_float_test() const;
	float vector_float_test(int32 Index) const;
	int32 vector_float_test_size() const;
	void add_vector_float_test(float const& vector_float_test);
	void set_vector_float_test(TArray<float> const& vector_float_test);
	bool has_vector_float_test() const;
	TArray<FString> const& vector_string_test() const;
	FString const& vector_string_test(int32 Index) const;
	int32 vector_string_test_size() const;
	void add_vector_string_test(FString const& vector_string_test);
	void set_vector_string_test(TArray<FString> const& vector_string_test);
	bool has_vector_string_test() const;

private:
	bool bool_test_;
	bool has_bool_test_;
	int32 int32_test_;
	bool has_int32_test_;
	int64 int64_test_;
	bool has_int64_test_;
	float float_test_;
	bool has_float_test_;
	FString string_test_;
	bool has_string_test_;
	TArray<bool> vector_bool_test_;
	TArray<int32> vector_int32_test_;
	TArray<int64> vector_int64_test_;
	TArray<float> vector_float_test_;
	TArray<FString> vector_string_test_;
};

class NetRequestTestLogin : public NetRequestBase
{
public:
	NetRequestTestLogin();

	static NetRequestTestLogin* Cast(NetRequestBase& Data);

	virtual NetRequestBase* Create() const override;

	virtual void Clear() override;

	virtual FString ParseStr() override;

public:
	FString const& username() const;
	void set_username(FString const& username);
	bool has_username() const;
	FString const& password() const;
	void set_password(FString const& password);
	bool has_password() const;

private:
	FString username_;
	bool has_username_;
	FString password_;
	bool has_password_;
};

class NetRequestTestLogout : public NetRequestBase
{
public:
	NetRequestTestLogout();

	static NetRequestTestLogout* Cast(NetRequestBase& Data);

	virtual NetRequestBase* Create() const override;

	virtual void Clear() override;

	virtual FString ParseStr() override;
};
