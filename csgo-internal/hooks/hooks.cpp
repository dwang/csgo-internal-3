#include "hooks.hpp"

#include "../sdk/interfaces/interfaces.hpp"

namespace hooks
{
	std::unique_ptr<vmt_hook> client_hook;
	std::unique_ptr<vmt_hook> clientmode_hook;

	void initialize()
	{
		client_hook = std::make_unique<vmt_hook>();
		clientmode_hook = std::make_unique<vmt_hook>();

		client_hook->setup(interfaces::client);
		client_hook->hook<indexes::frame_stage_notify>(frame_stage_notify);

		clientmode_hook->setup(interfaces::clientmode);
		clientmode_hook->hook<indexes::create_move>(create_move);
	}

	void restore()
	{
		client_hook->release();
		clientmode_hook->release();
	}

	bool __stdcall create_move(float frame_time, c_usercmd* user_cmd)
	{
		static auto original_fn = clientmode_hook->get_original<create_move_fn>(indexes::create_move);
		original_fn(interfaces::clientmode, frame_time, user_cmd);

		if (!user_cmd || !user_cmd->command_number)
			return original_fn;

		return false;
	}

	void __stdcall frame_stage_notify(int frame_stage)
	{
		static auto original_fn = client_hook->get_original<frame_stage_notify_fn>(indexes::frame_stage_notify);
		original_fn(interfaces::client, frame_stage);
	}
}
