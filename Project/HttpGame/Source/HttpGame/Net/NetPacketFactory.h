#pragma once

template <typename NetPacketType>
class NetPacketFactory
{
public:
	NetPacketFactory()
	{
	};

	~NetPacketFactory()
	{
		SAFE_DELETE(NetPacketInstance_);
	}

	static NetPacketType& Get()
	{
		if (!NetPacketInstance_)
		{
			NetPacketInstance_ = new NetPacketType();
		}
		else
		{
			NetPacketInstance_->Clear();
		}
		return *NetPacketInstance_;
	}

private:
	static NetPacketType* NetPacketInstance_;
};

template <typename T>
T* NetPacketFactory<T>::NetPacketInstance_ = nullptr;
