#ifndef __SIM_OBJECT_POOL_H__
#define __SIM_OBJECT_POOL_H__

#include <list>
#include <vector>

namespace dida
{
#define DECLARE_OBJECT_POOL_ID(ObjectId) \
	public: \
		int32 Get##ObjectId() { return GetObjectPoolId(); } \
		void Set##ObjectId(int32 id) { SetObjectPoolId(id); }

	class SimObjectItem
	{
	public:
		SimObjectItem() { object_pool_id_ = -1; }
		virtual ~SimObjectItem() = default;
		virtual void Clear() = 0;
		int32 GetObjectPoolId() const { return object_pool_id_; }
		void SetObjectPoolId(int32 id) { object_pool_id_ = id; }
	private:
		int32 object_pool_id_;
	};

	template <typename ObjectType, int32 MaxSize>
	class SimObjectPool
	{
		using object_recycle_type = std::list<int32>;

	public:
		SimObjectPool()
			: pool_size_max_(MaxSize)
		{
			recycle_object_index_.clear();
			for (int32 i = 0; i < pool_size_max_; ++i)
			{
				object_pool_[i].SetObjectPoolId(i);
				recycle_object_index_.emplace_back(i);
			}
		}

		~SimObjectPool()
		{
		}

		void Reset()
		{
			recycle_object_index_.clear();
			for (int32 i = 0; i < pool_size_max_; ++i)
			{
				recycle_object_index_.emplace_back(i);
			}
		}

		ObjectType* Spawn()
		{
			if (recycle_object_index_.empty())
			{
				return nullptr;
			}
			const int32 object_index = recycle_object_index_.front();
			recycle_object_index_.pop_front();
			if (object_index >= 0 && object_index < pool_size_max_)
			{
				object_pool_[object_index].Clear();
				return &object_pool_[object_index];
			}
			return nullptr;
		}

		ObjectType* Get(int32 object_id)
		{
			if (object_id >= 0 && object_id < pool_size_max_)
			{
				return &object_pool_[object_id];
			}
			return nullptr;
		}

		void Recycle(ObjectType* object_ptr)
		{
			if (object_ptr == nullptr)
			{
				return;
			}
			const int object_id = object_ptr->GetObjectPoolId();
			if (object_id >= 0 && object_id < pool_size_max_)
			{
				recycle_object_index_.emplace_back(object_id);
			}
		}

		void Recycle(int32 object_id)
		{
			if (object_id >= 0 && object_id < pool_size_max_)
			{
				recycle_object_index_.emplace_back(object_id);
			}
		}

	private:
		int32 pool_size_max_;
		ObjectType object_pool_[MaxSize];
		object_recycle_type recycle_object_index_;
	};

	template <typename ObjectType, int32 MaxSize>
	class ExpandObjectPool
	{
		using object_recycle_type = std::list<int32>;

	public:
		ExpandObjectPool()
			: pool_size_max_(MaxSize)
		{
			recycle_object_index_.clear();

			object_pool_.reserve(pool_size_max_);
			for (int32 i = 0; i < pool_size_max_; ++i)
			{
				ObjectType object;
				object.SetObjectPoolId(i);
				object_pool_.emplace_back(object);
				recycle_object_index_.emplace_back(i);
			}
		}

		~ExpandObjectPool()
		{
		}

		void Reset()
		{
			recycle_object_index_.clear();
			for (int32 i = 0; i < pool_size_max_; ++i)
			{
				recycle_object_index_.emplace_back(i);
			}
		}

		ObjectType* Spawn()
		{
			if (recycle_object_index_.empty())
			{
				int32 pool_id = pool_size_max_++;
				ObjectType object;
				object.SetObjectPoolId(pool_id);
				object_pool_.emplace_back(object);
				recycle_object_index_.emplace_back(pool_id);
			}
			const int32 object_index = recycle_object_index_.front();
			recycle_object_index_.pop_front();
			if (object_index >= 0 && object_index < pool_size_max_)
			{
				object_pool_[object_index].Clear();
				return &object_pool_[object_index];
			}
			return nullptr;
		}

		ObjectType* Get(int32 object_id)
		{
			if (object_id >= 0 && object_id < pool_size_max_)
			{
				return &object_pool_[object_id];
			}
			return nullptr;
		}

		void Recycle(ObjectType* object_ptr)
		{
			if (object_ptr == nullptr)
			{
				return;
			}
			const int object_id = object_ptr->GetObjectPoolId();
			if (object_id >= 0 && object_id < pool_size_max_)
			{
				recycle_object_index_.push_back(object_id);
			}
		}

	private:
		int32 pool_size_max_;
		std::vector<ObjectType> object_pool_;
		object_recycle_type recycle_object_index_;
	};
}

#endif
