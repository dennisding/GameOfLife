
#include "cosmos.hpp"

Cosmos::Cosmos() : generation_(0)
{
}

void Cosmos::stop()
{
	thread_pool_.stop_all();
}

void Cosmos::add_life(i64 x, i64 y)
{
	Life* life = current_allocator_.allocate(x, y);

	lifes_.insert(life);
}

int Cosmos::evolve(int step)
{
	for (int index = 0; index < step; ++index) {
		generation_ += 1;

		update_cosmos();
	}
	return generation_;
}

int Cosmos::async_evolve(int step)
{
	for (int index = 0; index < step; ++index) {
		generation_ += 1;

		async_update_cosmos();
	}

	return generation_;
}

void Cosmos::update_cosmos()
{
	LifeSet updated;
	LifeSet new_lifes;
	NullOwnershipHolder ownership_holder;

	for (auto& life : lifes_) {
		update_neighbors(life, updated, new_lifes, ownership_holder);
	}

	lifes_.swap(new_lifes);
	current_allocator_.swap(new_life_allocator_);
	new_life_allocator_.reset();
}

void Cosmos::async_update_cosmos()
{
	thread_pool_.init();
	LifeSet updated;
	LifeSet new_lifes;
	OwnershipHolder ownership_holder;

	std::atomic<size_t> counter_(0);

	for (auto& life : lifes_) {
		thread_pool_.add_task([&]() {
			update_neighbors(life, updated, new_lifes, ownership_holder);
			counter_.fetch_add(1, std::memory_order_relaxed);
			});
	}

	// wait all task done
	while (counter_.load(std::memory_order_acquire) != lifes_.size());

	lifes_.swap(new_lifes);
	current_allocator_.swap(new_life_allocator_);
	new_life_allocator_.reset();
}

// check the neighbor in the following order
// x00      0x0      00x
// x00  ->  000  ->  00x
// x00      0x0      00x
int Cosmos::count_neighbors(const Life* life)
{
	int count = 0;

	for (int index = -1; index < 2; ++index) {
		Life bounder_life(life->x + index, life->y - 1);

		int step = 0;
		auto life_iter = lifes_.lower_bound(&bounder_life);
		while ((step < 3) && (life_iter != lifes_.end())) {
			if ((*life_iter)->x != bounder_life.x) { // not in the same colum, next iter
				break;
			}
			if ((*life_iter)->is_me(life)) { // it's me, do nothing

			}
			else if ((*life_iter)->is_neighbor(life)) {
				++count;
			}

			// next iter
			++step;
			++life_iter;
		}
	}

	return count;
}

void Cosmos::capture(LifeSet& lifes, i64 x, i64 y, int range)
{
	i64 min_x = x - range;
	i64 min_y = y - range;
	i64 max_x = x + range;
	i64 max_y = y + range;
	// we need to deal with overflow here.
	if (min_x > max_x) {
		std::swap(min_x, max_x);
	}
	if (min_y > max_y) {
		std::swap(min_y, max_y);
	}

	for (i64 xindex = min_x; xindex < max_x; ++xindex) {
		Life life(xindex, min_y);
		auto lower_bound = lifes_.lower_bound(&life);
		while (lower_bound != lifes_.end()) {
			if ((*lower_bound)->x != xindex) { // no more life in this colum
				break;
			}
			if ((*lower_bound)->y > max_y) { // out of range in this colum
				break;
			}
			// captured
			lifes.insert(*lower_bound);
			++lower_bound;
		}
	}
}

bool Cosmos::heat_death()
{
	return lifes_.empty();
}

bool Cosmos::operator==(const Cosmos& right) const
{
	if (lifes_.size() != right.lifes_.size()) {
		return false;
	}
	auto iter = lifes_.begin();
	auto right_iter = right.lifes_.begin();
	while (iter != lifes_.end()) {
		if (!(**iter == **right_iter)) {
			return false;
		}
		// equal size
		++iter;
		++right_iter;
	}

	return true;
}

void Cosmos::reset()
{
	lifes_.clear();
	current_allocator_.reset();
	new_life_allocator_.reset();
	generation_ = 0;
}

bool Cosmos::is_alive(Life life) const
{
	return lifes_.find(&life) != lifes_.end();
}

const Cosmos::Iterator Cosmos::begin() const
{
	return Iterator(lifes_.begin());
}

const Cosmos::Iterator Cosmos::end() const
{
	return Iterator(lifes_.end());
}

