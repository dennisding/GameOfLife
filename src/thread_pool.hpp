#pragma once

#include <memory>
#include <thread>
#include <vector>
#include <functional>

#include <list>
#include <atomic>

class OwnershipHolder
{
public:
	inline OwnershipHolder() : ownership_(1) {}

	inline void take() { while (!ownership_.exchange(0, std::memory_order_acquire)); }
	inline void release() { ownership_.exchange(1, std::memory_order_release); }

private:
	std::atomic<int> ownership_;
};

class NullOwnershipHolder
{
public:
	inline void take() {}
	inline void release() {}
};

class ThreadPool
{
	using ThreadPtr = std::shared_ptr<std::thread>;
	using ThreadVector = std::vector<ThreadPtr>;
	using TaskPtr = std::function<void()>;
	using TaskList = std::list<TaskPtr>;
public:
	ThreadPool();

	// 可以多次调用
	void init(size_t thread_number = 0);
	void add_task(const TaskPtr& task);
	void stop_all();

private:
	ThreadPtr create_thread(const std::string &name = "<unknow>");

private:
	bool terminate_;
	std::atomic<int> tasks_ownership_;
	TaskList tasks_;
	ThreadVector threads_;
};