#include "../UnityEngine.CoreModule.hpp"
#include "../../ScriptInternal.hpp"
#include "Screen.hpp"

void* get_width_addr = nullptr;

void* get_height_addr = nullptr;

void* get_fullScreen_addr = nullptr;

void* get_currentResolution_Injected_addr = nullptr;

void* RequestOrientation_addr = nullptr;

static void InitAddress()
{
	get_width_addr = il2cpp_resolve_icall("UnityEngine.Screen::get_width()");
	get_height_addr = il2cpp_resolve_icall("UnityEngine.Screen::get_height()");
	get_fullScreen_addr = il2cpp_resolve_icall("UnityEngine.Screen::get_fullScreen()");
	get_currentResolution_Injected_addr = il2cpp_resolve_icall("UnityEngine.Screen::get_currentResolution_Injected()");
	RequestOrientation_addr = il2cpp_resolve_icall("UnityEngine.Screen::RequestOrientation()");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
}

namespace UnityEngine
{
	int Screen::width()
	{
		return reinterpret_cast<decltype(width)*>(get_width_addr)();
	}

	int Screen::height()
	{
		return reinterpret_cast<decltype(height)*>(get_height_addr)();
	}
	
	bool Screen::fullScreen()
	{
		return reinterpret_cast<decltype(fullScreen)*>(get_fullScreen_addr)();
	}

	Resolution Screen::currentResolution()
	{
		Resolution resolution;
		reinterpret_cast<void (*)(UnityEngine::Resolution*)>(get_currentResolution_Injected_addr)(&resolution);
		return resolution;
	}
	
	void Screen::RequestOrientation(ScreenOrientation orientation)
	{
		return reinterpret_cast<decltype(RequestOrientation)*>(RequestOrientation_addr)(orientation);
	}
}
