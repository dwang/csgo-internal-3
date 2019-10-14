#include "interfaces.hpp"

#include <Windows.h>
#include <cstdio>
#include <cstdint>

void* capture_interface(const char* mod_name, const char* interface_name)
{
	using fn_capture_iface_t = void* (*)(const char*, int*);
	auto fn_addr = reinterpret_cast<fn_capture_iface_t>(GetProcAddress(GetModuleHandleA(mod_name), "CreateInterface"));

	auto iface_addr = fn_addr(interface_name, nullptr);
	printf("Found %s at 0x%p\n", interface_name, iface_addr);

	return iface_addr;
}

namespace interfaces
{
	i_base_client_dll* client = nullptr;
	i_client_mode* clientmode = nullptr;

	void initialize()
	{
		client = reinterpret_cast<i_base_client_dll*>(capture_interface("client_panorama.dll", "VClient018"));

		clientmode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<std::uintptr_t**>(client))[10] + 5);
	}
}