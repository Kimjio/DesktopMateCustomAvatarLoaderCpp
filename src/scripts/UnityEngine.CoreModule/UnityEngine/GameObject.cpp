#include "../UnityEngine.CoreModule.hpp"
#include "../../ScriptInternal.hpp"
#include "GameObject.hpp"

void* Internal_CreateGameObject_addr = nullptr;

void* Internal_CreateGameObject_orig = nullptr;

void* Internal_AddComponentWithType_addr = nullptr;

void* Internal_AddComponentWithType_orig = nullptr;

void* TryGetComponentFastPath_addr = nullptr;

void* TryGetComponentFastPath_orig = nullptr;

void* GetComponent_addr = nullptr;

void* GetComponentByName_addr = nullptr;

void* GameObject_get_transform_addr = nullptr;

void* get_tag_addr = nullptr;

void* set_tag_addr = nullptr;

void* SetActive_addr = nullptr;

void* Find_addr = nullptr;

static void InitAddress()
{
	Internal_CreateGameObject_addr = il2cpp_resolve_icall("UnityEngine.GameObject::Internal_CreateGameObject()");
	Internal_AddComponentWithType_addr = il2cpp_resolve_icall("UnityEngine.GameObject::Internal_AddComponentWithType()");
	TryGetComponentFastPath_addr = il2cpp_resolve_icall("UnityEngine.GameObject::TryGetComponentFastPath()");
	GetComponent_addr = il2cpp_resolve_icall("UnityEngine.GameObject::GetComponent()");
	GetComponentByName_addr = il2cpp_resolve_icall("UnityEngine.GameObject::GetComponentByName()");
	GameObject_get_transform_addr = il2cpp_resolve_icall("UnityEngine.GameObject::get_transform()");
	get_tag_addr = il2cpp_resolve_icall("UnityEngine.GameObject::get_tag()");
	set_tag_addr = il2cpp_resolve_icall("UnityEngine.GameObject::set_tag()");
	SetActive_addr = il2cpp_resolve_icall("UnityEngine.GameObject::SetActive()");
	Find_addr = il2cpp_resolve_icall("UnityEngine.GameObject::Find()");
}

STATIC
{
	il2cpp_symbols::init_callbacks.emplace_back(InitAddress);
}

namespace UnityEngine
{
	GameObject::GameObject(Il2CppString* name) : Object::Object(nullptr)
	{
		auto gameObject = il2cpp_object_new(il2cpp_symbols::get_class(ASSEMBLY_NAME, "UnityEngine", "GameObject"));
		Internal_CreateGameObject(gameObject, name);
		this->instance = gameObject;
	}

	GameObject GameObject::Find(Il2CppString* name)
	{
		auto gameObject = reinterpret_cast<Il2CppObject * (*)(Il2CppString*)>(Find_addr)(name);
		return GameObject(gameObject);
	}

	void GameObject::Internal_CreateGameObject(Il2CppObject* self, Il2CppString* name)
	{
		reinterpret_cast<decltype(Internal_CreateGameObject)*>(Internal_CreateGameObject_addr)(self, name);
	}

	Il2CppObject* GameObject::Internal_AddComponentWithType(Il2CppObject* runtimeType)
	{
		return reinterpret_cast<Il2CppObject * (*)(Il2CppObject*, Il2CppObject*)>(Internal_AddComponentWithType_addr)(instance, runtimeType);
	}

	Il2CppObject* GameObject::GetComponent(Il2CppObject* runtimeType)
	{
		return reinterpret_cast<Il2CppObject * (*)(Il2CppObject*, Il2CppObject*)>(GetComponent_addr)(instance, runtimeType);
	}

	Il2CppObject* GameObject::GetComponentByName(Il2CppString* name)
	{
		return reinterpret_cast<Il2CppObject * (*)(Il2CppObject*, Il2CppString*)>(GetComponentByName_addr)(instance, name);
	}

	Transform GameObject::transform()
	{
		auto transform = reinterpret_cast<Il2CppObject * (*)(Il2CppObject*)>(GameObject_get_transform_addr)(instance);
		return Transform(transform);
	}

	Il2CppString* GameObject::tag()
	{
		return reinterpret_cast<Il2CppString * (*)(Il2CppObject*)>(get_tag_addr)(instance);
	}

	void GameObject::tag(Il2CppString* value)
	{
		reinterpret_cast<void (*)(Il2CppObject*, Il2CppString*)>(set_tag_addr)(instance, value);
	}

	void GameObject::SetActive(bool value)
	{
		reinterpret_cast<void (*)(Il2CppObject*, bool)>(SetActive_addr)(instance, value);
	}
}
