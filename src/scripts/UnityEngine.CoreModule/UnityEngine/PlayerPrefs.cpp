#include "../UnityEngine.CoreModule.hpp"
#include "../../ScriptInternal.hpp"
#include "PlayerPrefs.hpp"


void* TrySetInt_addr = nullptr;

void* TrySetFloat_addr = nullptr;

void* TrySetSetString_addr = nullptr;

void* GetInt_addr = nullptr;

void* GetFloat_addr = nullptr;

void* GetString_addr = nullptr;

void* HasKey_addr = nullptr;

void* DeleteKey_addr = nullptr;

void* DeleteAll_addr = nullptr;

void* Save_addr = nullptr;


static void InitAddress()
{
	TrySetInt_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::TrySetInt()");
	TrySetFloat_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::TrySetFloat()");
	TrySetSetString_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::TrySetSetString()");
	GetInt_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::GetInt()");
	GetFloat_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::GetFloat()");
	GetString_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::GetString()");
	HasKey_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::HasKey()");
	DeleteKey_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::DeleteKey()");
	DeleteAll_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::DeleteAll()");
	Save_addr = il2cpp_resolve_icall("UnityEngine.PlayerPrefs::Save()");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
}

namespace UnityEngine
{
	bool PlayerPrefs::TrySetInt(Il2CppString* key, int value)
	{
		return reinterpret_cast<decltype(TrySetInt)*>(TrySetInt_addr)(key, value);
	}

	bool PlayerPrefs::TrySetFloat(Il2CppString* key, float value)
	{
		return reinterpret_cast<decltype(TrySetFloat)*>(TrySetFloat_addr)(key, value);
	}

	bool PlayerPrefs::TrySetSetString(Il2CppString* key, Il2CppString* value)
	{
		return reinterpret_cast<decltype(TrySetSetString)*>(TrySetSetString_addr)(key, value);
	}

	int PlayerPrefs::GetInt(Il2CppString* key, int defaultValue)
	{
		return reinterpret_cast<decltype(GetInt)*>(GetInt_addr)(key, defaultValue);
	}

	float PlayerPrefs::GetFloat(Il2CppString* key, float defaultValue)
	{
		return reinterpret_cast<decltype(GetFloat)*>(GetFloat_addr)(key, defaultValue);
	}

	Il2CppString* PlayerPrefs::GetString(Il2CppString* key, Il2CppString* defaultValue)
	{
		return reinterpret_cast<decltype(GetString)*>(GetString_addr)(key, defaultValue);
	}

	bool PlayerPrefs::HasKey(Il2CppString* key)
	{
		return reinterpret_cast<decltype(HasKey)*>(HasKey_addr)(key);
	}

	void PlayerPrefs::DeleteKey(Il2CppString* key)
	{
		reinterpret_cast<decltype(DeleteKey)*>(DeleteKey_addr)(key);
	}

	void PlayerPrefs::DeleteAll()
	{
		reinterpret_cast<decltype(DeleteAll)*>(DeleteAll_addr)();
	}

	void PlayerPrefs::Save()
	{
		reinterpret_cast<decltype(Save)*>(Save_addr)();
	}
}
