#include <stdinclude.hpp>

extern bool init_hook();
extern void uninit_hook();

using namespace std;

static BOOL WINAPI AttachOrCreateConsole()
{
	if (AttachConsole(ATTACH_PARENT_PROCESS))
	{
		return TRUE;
	}

	return AllocConsole();
}

static void create_debug_console()
{
	AttachOrCreateConsole();

	// open stdout stream
	auto _ = freopen("CONOUT$", "w+t", stdout);
	_ = freopen("CONOUT$", "w", stderr);
	_ = freopen("CONIN$", "r", stdin);

	SetConsoleTitleW(L"DesktopMate - Debug Console");

	// set this to avoid turn japanese texts into question mark
	SetConsoleOutputCP(CP_UTF8);
	locale::global(locale(".UTF-8"));

	wcout << L"DesktopMate Patch Loaded! - By Kimjio" << endl;
}

int __stdcall DllMain(HINSTANCE, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		string module_name;
		module_name.resize(MAX_PATH);
		module_name.resize(GetModuleFileNameA(nullptr, module_name.data(), MAX_PATH));

		filesystem::path module_path(module_name);

		// check name
		if (module_path.filename() != "DesktopMate.exe")
			return 1;

		std::filesystem::current_path(
			module_path.parent_path()
		);

		auto commandLine = GetCommandLineW();
		int argc = 0;
		auto argv = CommandLineToArgvW(commandLine, &argc);

		bool isEnableConsole = false;

		for (auto i = 0; i < argc; i++)
		{
			if (argv[i] == L"--console"s)
			{
				isEnableConsole = true;
				break;
			}
		}

		if (isEnableConsole)
		{
			create_debug_console();
		}

		init_hook();
	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		uninit_hook();
	}

	return 1;
}
