#define VC_EXTRALEAN
#include <Windows.h>
#include <thread>
#include <iostream>

#include "sdk/interfaces/interfaces.hpp"
#include "utilities/netvars.hpp"
#include "hooks/hooks.hpp"

DWORD WINAPI detach()
{
	hooks::restore();

#ifdef _DEBUG
	fclose(reinterpret_cast<FILE*>(stdin));
	fclose(reinterpret_cast<FILE*>(stdout));
	FreeConsole();
#endif

	return TRUE;
}

DWORD WINAPI entry(LPVOID lpThreadParameter)
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif

	interfaces::initialize();
	
	netvar_manager::get().initialize(interfaces::client->get_client_classes());
#ifdef _DEBUG
	netvar_manager::get().dump_netvars(interfaces::client->get_client_classes());
#endif

	hooks::initialize();

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	std::this_thread::sleep_for(std::chrono::milliseconds(400));

	detach();

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpThreadParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		if (auto handle = CreateThread(nullptr, NULL, entry, hinstDLL, NULL, nullptr))
		{
			CloseHandle(handle);
		}
	}
	else if (fdwReason == DLL_PROCESS_DETACH && !lpvReserved)
	{
		return detach();
	}

	return TRUE;
}

