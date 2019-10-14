#pragma once

#include <Windows.h>
#include <stdexcept>
#include <cstdint>
#include <memory>

class protect_guard
{
private:
	void* base;
	std::size_t length;
	std::uint32_t old;

public:
	protect_guard(void* base, std::size_t length, std::uint32_t flags);
	~protect_guard();

};

class vmt_hook
{
private:
	std::size_t table_length;
	bool is_allocated;

	void* class_base;
	std::uintptr_t* new_table;
	std::uintptr_t* old_table;

	std::size_t estimate_table_length(std::uintptr_t* table_start);

public:
	void setup(void* class_base);
	void release();

	template <std::size_t index, typename fn>
	void hook(fn function)
	{
		if (index < 0 || index > this->table_length)
			return;

		this->new_table[index + 1] = reinterpret_cast<std::uintptr_t>(function);
	}

	template <typename fn>
	fn get_original(const size_t index)
	{
		return reinterpret_cast<fn>(this->old_table[index]);
	}
};
