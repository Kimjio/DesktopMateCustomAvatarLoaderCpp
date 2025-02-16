#pragma once
#include "il2cpp/il2cpp_symbols.hpp"

namespace UnityEngine
{
	class PlayerPrefs
	{
	public:
		static bool TrySetInt(Il2CppString* key, int value);

		static bool TrySetFloat(Il2CppString* key, float value);
		
		static bool TrySetSetString(Il2CppString* key, Il2CppString* value);

		static int GetInt(Il2CppString* key, int defaultValue = 0);

		static float GetFloat(Il2CppString* key, float defaultValue = 0);

		static Il2CppString* GetString(Il2CppString* key, Il2CppString* defaultValue = il2cpp_string_new(""));

		static bool HasKey(Il2CppString* key);

		static void DeleteKey(Il2CppString* key);

		static void DeleteAll();

		static void Save();
	};
}
