#pragma once

#include "i_base_client_dll.hpp"
#include "i_client_mode.hpp"

namespace interfaces
{
	extern i_base_client_dll* client;
	extern i_client_mode* clientmode;

	void initialize();
}