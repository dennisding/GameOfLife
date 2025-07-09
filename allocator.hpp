#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#define CHUNK_SIZE (4096)

template <typename Type>
class Allocator
{
public:
	Allocator() : index_(0)
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
		int chunk_index = index_ / CHUNK_SIZE;
		int index = index_ % CHUNK_SIZE;
		if (chunks_.size() <= chunk_index) {
			// allocate new space
			chunks_.push_back(new char[sizeof(Type)* CHUNK_SIZE]);
		}

		index_ += 1;
		void* memory = (Type*)chunks_[chunk_index] + index;
		return new(memory) Type(std::forward<ArgTypes>(args)...);
	}

	void reset()
	{
		index_ = 0;
	}

	void swap(Allocator& other)
	{
		std::swap(index_, other.index_);
		std::swap(chunks_, other.chunks_);
	}
	
private:
	int index_;
	std::vector<void*> chunks_;
};