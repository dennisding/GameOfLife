#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <atomic>

#define CHUNK_SIZE (4096)

template <typename Type>
class Allocator
{
public:
	Allocator() : index_(0), ownership_(1)
	{
	}

	~Allocator()
	{
		for (auto It : chunks_) {
			delete It;
		}
	}

	template <typename ...ArgTypes>
	Type* allocate(ArgTypes ...args)
	{
		// acquire owner ship
		while (!ownership_.exchange(0, std::memory_order_acquire));

		int chunk_index = index_ / CHUNK_SIZE;
		int index = index_ % CHUNK_SIZE;
		if (chunks_.size() <= chunk_index) {
			// allocate new space
			chunks_.push_back(new char[sizeof(Type)* CHUNK_SIZE]);
		}

		index_ += 1;
		void* memory = (Type*)chunks_[chunk_index] + index;
		
		// release ownership
		ownership_.exchange(1, std::memory_order_release);

		return new(memory) Type(std::forward<ArgTypes>(args)...);
	}

	void reset()
	{
		// acquire owner ship
		while (!ownership_.exchange(0, std::memory_order_acquire));

		index_ = 0;

		// release ownership
		ownership_.exchange(1, std::memory_order_release);
	}

	void swap(Allocator& other)
	{
		// acquire owner ship
		while (!ownership_.exchange(0, std::memory_order_acquire));

		std::swap(index_, other.index_);
		std::swap(chunks_, other.chunks_);

		// release ownership
		ownership_.exchange(1, std::memory_order_release);
	}
	
private:
	int index_;
	std::atomic<int> ownership_;
	std::vector<void*> chunks_;
};
