#include "../UnityEngine.CoreModule.hpp"
#include "../../ScriptInternal.hpp"
#include "MonoBehaviour.hpp"
#include "Color.hpp"
#include "Coroutine.hpp"
#include "Screen.hpp"

#include <thread>

#include "scripts/UnityEngine.AssetBundleModule/UnityEngine/AssetBundle.hpp"

void* StartCoroutineManaged2_addr = nullptr;
void* StartCoroutineManaged2_orig = nullptr;

static Il2CppObject* StartCoroutineManaged2_hook(Il2CppObject* self, Il2CppObject* enumerator)
{
	return reinterpret_cast<decltype(StartCoroutineManaged2_hook)*>(StartCoroutineManaged2_orig)(self, enumerator);
}

static void InitAddress()
{
	StartCoroutineManaged2_addr = il2cpp_resolve_icall("UnityEngine.MonoBehaviour::StartCoroutineManaged2()");
}

static void HookMethods()
{
	ADD_HOOK(StartCoroutineManaged2, "UnityEngine.MonoBehaviour::StartCoroutineManaged2 at %p\n");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
	// il2cpp_symbols::init_callbacks.emplace_back(HookMethods);
}

namespace UnityEngine
{
	Coroutine MonoBehaviour::StartCoroutineManaged2(Il2CppObject* enumerator)
	{
		auto object = reinterpret_cast<Il2CppObject * (*)(Il2CppObject*, Il2CppObject*)>(StartCoroutineManaged2_addr)(instance, enumerator);
		return Coroutine(object);
	}
}
