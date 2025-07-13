
#include "thread_pool.hpp"

ThreadPool::ThreadPool() : tasks_ownership_(1), terminate_(false)
{

}

void ThreadPool::init(size_t thread_number)
{
	if (!threads_.empty()) {
		// init once
		return;
	}

	if (thread_number == 0) {
		thread_number = std::thread::hardware_concurrency();
	}

	for (int index = 0; index < thread_number; ++index) {
		threads_.push_back(create_thread());
	}
}

std::shared_ptr<std::thread> ThreadPool::create_thread(const std::string& name)
{
	return std::make_shared<std::thread>([this]() {
		for (;;) {
			// get the tasks_ ownership
			while (!tasks_ownership_.exchange(0, std::memory_order_acquire));

			auto task_iter = tasks_.begin();
			TaskPtr task;
			if (task_iter != tasks_.end()) {
				// get the task
				task = *task_iter;
				tasks_.erase(task_iter);
			}
			// free the tasks ownership
			tasks_ownership_.exchange(1, std::memory_order_release);
			if (terminate_) {
				break;
			}

			// del the task
			if (task) {
				task();
			}
			else // sleep for a while
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		});
}

void ThreadPool::add_task(const TaskPtr& task)
{
	while (!tasks_ownership_.exchange(0, std::memory_order_acquire));

	tasks_.push_back(task);

	tasks_ownership_.exchange(1, std::memory_order_release);
}

void ThreadPool::stop_all()
{
	terminate_ = true;
	for (auto thread : threads_) {
		thread->join();
	}
}