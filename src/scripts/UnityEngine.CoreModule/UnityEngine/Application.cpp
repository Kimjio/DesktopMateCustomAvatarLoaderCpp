#include "../UnityEngine.CoreModule.hpp"
#include "../../ScriptInternal.hpp"
#include "Application.hpp"

#include <filesystem>

void* Quit_addr = nullptr;

void* OpenURL_addr = nullptr;

void* get_unityVersion_addr = nullptr;

void* get_companyName_addr = nullptr;

void* get_productName_addr = nullptr;

void* get_dataPath_addr = nullptr;

void* get_persistentDataPath_addr = nullptr;

void* set_targetFrameRate_addr = nullptr;

static void InitAddress()
{
	Quit_addr = il2cpp_resolve_icall("UnityEngine.Application::Quit(System.Int32)");
	OpenURL_addr = il2cpp_symbols::get_method_pointer(ASSEMBLY_NAME, "UnityEngine", "Application", "OpenURL", 1);
	get_unityVersion_addr = il2cpp_resolve_icall("UnityEngine.Application::get_unityVersion()");
	get_companyName_addr = il2cpp_resolve_icall("UnityEngine.Application::get_companyName()");
	get_productName_addr = il2cpp_resolve_icall("UnityEngine.Application::get_productName()");
	get_dataPath_addr = il2cpp_resolve_icall("UnityEngine.Application::get_dataPath()");
	get_persistentDataPath_addr = il2cpp_resolve_icall("UnityEngine.Application::get_persistentDataPath()");
	set_targetFrameRate_addr = il2cpp_resolve_icall("UnityEngine.Application::set_targetFrameRate(System.Int32)");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
}

namespace UnityEngine
{
	void Application::Quit(int exitCode)
	{
		reinterpret_cast<decltype(Quit)*>(Quit_addr)(exitCode);
	}

	void Application::OpenURL(Il2CppString* url)
	{
		reinterpret_cast<decltype(OpenURL)*>(OpenURL_addr)(url);
	}

	Il2CppString* Application::unityVersion()
	{
		return reinterpret_cast<Il2CppString * (*)()>(get_unityVersion_addr)();
	}

	Il2CppString* Application::companyName()
	{
		return reinterpret_cast<Il2CppString * (*)()>(get_companyName_addr)();
	}

	Il2CppString* Application::productName()
	{
		return reinterpret_cast<Il2CppString * (*)()>(get_productName_addr)();
	}

	Il2CppString* Application::dataPath()
	{
		return reinterpret_cast<Il2CppString * (*)()>(get_dataPath_addr)();
	}

	Il2CppString* Application::persistentDataPath()
	{
		return reinterpret_cast<Il2CppString * (*)()>(get_persistentDataPath_addr)();
	}

	void Application::targetFrameRate(int value)
	{
		reinterpret_cast<decltype(targetFrameRate)*>(set_targetFrameRate_addr)(value);
	}

	void Application::Exit(int exitCode)
	{
		reinterpret_cast<decltype(Quit)*>(Quit_addr)(exitCode);
	}
}
