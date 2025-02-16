#include "../UnityEngine.AssetBundleModule.hpp"
#include "../../ScriptInternal.hpp"
#include "AssetBundle.hpp"

#include "scripts/UnityEngine.CoreModule/UnityEngine/Object.hpp"
#include "scripts/UnityEngine.CoreModule/UnityEngine/Shader.hpp"
#include "scripts/UnityEngine.CoreModule/UnityEngine/Material.hpp"

#include "string_utils.hpp"

void* LoadFromFile_Internal_addr = nullptr;

void* LoadAsset_Internal_addr = nullptr;

void* LoadAssetAsync_Internal_addr = nullptr;

void* GetAllAssetNames_addr = nullptr;

void* Unload_addr = nullptr;

static void InitAddress()
{
	LoadFromFile_Internal_addr = il2cpp_resolve_icall("UnityEngine.AssetBundle::LoadFromFile_Internal(System.String,System.UInt32,System.UInt64)");
	LoadAsset_Internal_addr = il2cpp_resolve_icall("UnityEngine.AssetBundle::LoadAsset_Internal(System.String,System.Type)");
	LoadAssetAsync_Internal_addr = il2cpp_resolve_icall("UnityEngine.AssetBundle::LoadAssetAsync_Internal(System.String,System.Type)");
	GetAllAssetNames_addr = il2cpp_resolve_icall("UnityEngine.AssetBundle::GetAllAssetNames()");
	Unload_addr = il2cpp_resolve_icall("UnityEngine.AssetBundle::Unload()");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
}

namespace UnityEngine
{
	AssetBundle AssetBundle::LoadFromFile(Il2CppString* path)
	{
		auto obj = reinterpret_cast<Il2CppObject * (*)(Il2CppString * path, uint32_t crc, uint64_t offset)>(LoadFromFile_Internal_addr)(path, 0, 0);
		return AssetBundle{ obj };
	}

	Il2CppObject* AssetBundle::LoadAsset(Il2CppString* name, Il2CppObject* runtimeType)
	{
		return reinterpret_cast<Il2CppObject * (*)(Il2CppObject * self, Il2CppString * name, Il2CppObject * type)>(LoadAsset_Internal_addr)(instance, name, runtimeType);
	}

	Il2CppObject* AssetBundle::LoadAssetAsync(Il2CppString* name, Il2CppObject* runtimeType)
	{
		return reinterpret_cast<Il2CppObject * (*)(Il2CppObject * self, Il2CppString * name, Il2CppObject * type)>(LoadAssetAsync_Internal_addr)(instance, name, runtimeType);
	}

	Il2CppArraySize_t<Il2CppString*>* AssetBundle::GetAllAssetNames()
	{
		return reinterpret_cast<Il2CppArraySize_t<Il2CppString*>* (*)(Il2CppObject*)>(GetAllAssetNames_addr)(instance);
	}

	void AssetBundle::Unload(bool unloadAllLoadedObjects)
	{
		reinterpret_cast<void (*)(Il2CppObject * self, bool unloadAllLoadedObjects)>(Unload_addr)(instance, unloadAllLoadedObjects);
	}
}
