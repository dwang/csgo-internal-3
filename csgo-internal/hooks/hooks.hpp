#pragma once

#include "../utilities/vmt.hpp"
#include "../sdk/interfaces/i_base_client_dll.hpp"
#include "../sdk/interfaces/i_client_mode.hpp"
#include "../sdk/classes/c_usercmd.hpp"

#include <memory>

namespace hooks
{
	extern std::unique_ptr<vmt_hook> client_hook;
	extern std::unique_ptr<vmt_hook> clientmode_hook;

	namespace indexes
	{
		constexpr auto create_move = 24;
		constexpr auto frame_stage_notify = 37;
	}

	using create_move_fn = bool(__thiscall*)(i_client_mode*, float, c_usercmd*);
	using frame_stage_notify_fn = void(__thiscall*)(i_base_client_dll*, int);

	bool __stdcall create_move(float frame_time, c_usercmd* user_cmd);
	void __stdcall frame_stage_notify(int frame_stage);

	void initialize();
	void restore();
}