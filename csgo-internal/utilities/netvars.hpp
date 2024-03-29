#pragma once

#include "singleton.hpp"
#include "fnv.hpp"

#include "../sdk/classes/recv_props.hpp"
#include "../sdk/classes/client_class.hpp"

#include <string>
#include <vector>
#include <map>
#include <fstream>

class netvar_manager : public singleton<netvar_manager>
{
private:
	std::map<unsigned int, recv_prop*> netvars_map;
	void dump_table_recursive(recv_table* table);
	void dump_table_to_file_recursive(recv_table* table, std::ofstream& file);

public:
	void initialize(client_class* client_data);
	void dump_netvars(client_class* client_data);

	unsigned short get_offset(unsigned int hash);
	recv_prop* get_prop(unsigned int hash);
};

#define offset_fn(type, var, offset) \
	type& var() \
	{ \
		return *(type*)(uintptr_t(this) + offset); \
	} \

#define netvar_fn(type, var, hash) \
	type& var() \
	{ \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return *(type*)(uintptr_t(this) + _offset); \
	} \

#define netvar_ptr_fn(type, var, hash) \
	type* var() \
	{ \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return (type*)(uintptr_t(this) + _offset); \
	} \

#define netvar_offset_fn(type, var, hash, offset) \
	type& var() \
	{ \
		static auto _offset = netvar_manager::get().get_offset(fnv_hash(hash)); \
		return *(type*)(uintptr_t(this) + _offset + offset); \
	} \

#define netvar_original(type, var, offset) \
	type& var() \
	{ \
		return *(type*)(uintptr_t(this) + offset); \
	} \
