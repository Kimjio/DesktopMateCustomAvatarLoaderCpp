#include <stdinclude.hpp>

#include <thread>

#include "il2cpp_dump.h"

#include "string_utils.hpp"

#include "scripts/ScriptInternal.hpp"

#include "scripts/UnityEngine.CoreModule/UnityEngine/Application.hpp"
#include "scripts/UnityEngine.CoreModule/UnityEngine/Debug.hpp"
#include "scripts/UnityEngine.CoreModule/UnityEngine/GameObject.hpp"
#include "scripts/UnityEngine.CoreModule/UnityEngine/PlayerPrefs.hpp"

using namespace std;

void* LoadLibraryW_orig = nullptr;

static void patch_game_assembly();

static void init_il2cpp()
{
	il2cpp_symbols::init_defaults();
	il2cpp_symbols::call_init_callbacks();

	patch_game_assembly();
}

void* il2cpp_init_orig = nullptr;
static bool __stdcall il2cpp_init_hook(const char* domain_name)
{
	const auto result = reinterpret_cast<decltype(il2cpp_init_hook)*>(il2cpp_init_orig)(domain_name);
	il2cpp_symbols::il2cpp_domain = il2cpp_domain_get();
	init_il2cpp();

	return result;
}

static HMODULE WINAPI LoadLibraryW_hook(LPCWSTR lpLibFileName)
{
	if (lpLibFileName == L"GameAssembly.dll"s)
	{
		const auto il2cpp = reinterpret_cast<decltype(LoadLibraryW)*>(LoadLibraryW_orig)(lpLibFileName);

		il2cpp_symbols::init_functions(il2cpp);

		MH_CreateHook(il2cpp_init, il2cpp_init_hook, &il2cpp_init_orig);
		MH_EnableHook(il2cpp_init);

		MH_DisableHook(LoadLibraryW);
		MH_RemoveHook(LoadLibraryW);

		return il2cpp;
	}

	return reinterpret_cast<decltype(LoadLibraryW)*>(LoadLibraryW_orig)(lpLibFileName);
}

static Il2CppObject* MigrateVrm0to1(Il2CppObject* glbData)
{
	Il2CppObject* vrmData = nullptr;
	Il2CppObject* migration = nullptr;
	auto res = il2cpp_symbols::get_method_pointer<Il2CppObject * (*)(Il2CppObject*, Il2CppObject**, Il2CppObject**)>("VRM10.dll", "", "vl", "iob", 3)(glbData, &vrmData, &migration);

	auto MessageField = il2cpp_class_get_field_from_name(migration->klass, "qps");
	Il2CppString* message = nullptr;
	il2cpp_field_get_value(migration, MessageField, &message);

	wcout << "VRM10 Migration: " << message->chars << endl;

	if (!vrmData)
	{
		cout << "VRM migration attempt failed. The avatar file might be corrupt or incompatible." << endl;
	}

	return vrmData;
}

static UnityEngine::GameObject LoadVrmIntoScene(wstring path)
{
	try
	{
		auto glbFileParser = il2cpp_object_new(il2cpp_symbols::get_class("UniGLTF.dll", "", "bfa"));
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, Il2CppString*)>(glbFileParser->klass, ".ctor", 1)->methodPointer(glbFileParser, il2cpp_string_new16(path.data()));
		auto data = il2cpp_class_get_method_from_name_type<Il2CppObject * (*)(Il2CppObject*)>(glbFileParser->klass, "fpq", 0)->methodPointer(glbFileParser);
		auto vrmData = il2cpp_symbols::get_method_pointer<Il2CppObject * (*)(Il2CppObject*)>("VRM10.dll", "", "vl", "ezl", 1)(data);

		// auto json = il2cpp_class_get_method_from_name_type<Il2CppString* (*)(Il2CppObject*)>(data->klass, "kht", 0)->methodPointer(data);
		// wcout << "JSON " << json->chars << endl;

		if (vrmData == nullptr)
		{
			cout << "VRM data is null, assuming it's VRM 0.0 avatar. Starting migration" << endl;
			vrmData = MigrateVrm0to1(data);

			if (vrmData == nullptr)
			{
				cout << "VRM data migration failed!" << endl;
				return nullptr;
			}

			cout << "VRM data migration succeeded!" << endl;
		}

		auto vrm10Importer = il2cpp_object_new(il2cpp_symbols::get_class("VRM10.dll", "", "wd"));
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, Il2CppObject*, Il2CppObject*, Il2CppObject*, Il2CppObject*, bool)>(vrm10Importer->klass, ".ctor", 5)->methodPointer(vrm10Importer, vrmData, nullptr, nullptr, nullptr, false);
		auto loaded = il2cpp_symbols::get_method_pointer<Il2CppObject * (*)(Il2CppObject*)>("UniGLTF.dll", "", "bcj", "klk", 1)(vrm10Importer);

		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*)>(loaded->klass, "kwr", 0)->methodPointer(loaded);
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*)>(loaded->klass, "kwq", 0)->methodPointer(loaded);


		UnityEngine::Object::Name(loaded, il2cpp_string_new("VRMFILE"));
		return UnityEngine::Component(loaded).gameObject();
	}
	catch (const Il2CppExceptionWrapper& e)
	{
		wcout << "Error trying to load the VRM file!: " << e.ex->message->chars << endl;
	}

	Il2CppObject* nptr = nullptr;
	return UnityEngine::GameObject(nptr);
}

static void CopyCharaData(Il2CppObject* source, Il2CppObject* target)
{
	void* iter = nullptr;
	while (FieldInfo* field = il2cpp_class_get_fields(source->klass, &iter))
	{
		void* value = nullptr;
		il2cpp_field_get_value(source, field, &value);
		il2cpp_field_set_value(target, field, value);
	}
}

static bool LoadCharacter(wstring path)
{
	try
	{
		if (!filesystem::exists(path))
		{
			wcerr << "[Chara Loader] VRM file does not exist: " << path << endl;
			return false;
		}

		auto CharaRoot = UnityEngine::GameObject::Find(il2cpp_string_new("/CharactersRoot"));

		auto chara = CharaRoot.transform().GetChild(0).gameObject();
		auto CharaData = chara.GetComponent(GetRuntimeType("Assembly-CSharp.dll", "", "CharaData"));

		auto animator = chara.GetComponent(GetRuntimeType("UnityEngine.AnimationModule.dll", "UnityEngine", "Animator"));
		auto RuntimeAnimatorController = il2cpp_class_get_method_from_name_type<Il2CppObject * (*)(Il2CppObject*)>(animator->klass, "get_runtimeAnimatorController", 0)->methodPointer(animator);

		cout << "Character attributes have been copied!" << endl;

		auto newChara = LoadVrmIntoScene(path);

		if (!newChara)
		{
			wcerr << "[Chara Loader] Failed to load VRM file: " << path << endl;

			thread([]()
				{
					MessageBoxW(nullptr, L"Failed to load VRM file! Make sure the VRM file is compatible!", L"Error", MB_ICONERROR);
				})
				.detach();

			return false;
		}

		cout << "Old character has been destroyed." << endl;
		UnityEngine::Object::Destroy(chara);

		newChara.transform().SetParent(CharaRoot.transform());

		auto newCharaData = newChara.AddComponent(GetRuntimeType("Assembly-CSharp.dll", "", "CharaData"));
		CopyCharaData(CharaData, newCharaData);

		Il2CppObject* manager = UnityEngine::GameObject::Find(il2cpp_string_new("MainManager")).GetComponent(GetRuntimeType("Assembly-CSharp.dll", "", "MainManager"));
		auto charaDataField = il2cpp_class_get_field_from_name(manager->klass, "charaData");
		il2cpp_field_set_value(manager, charaDataField, newCharaData);

		auto charaAnimator = newChara.GetComponent(GetRuntimeType("UnityEngine.AnimationModule.dll", "UnityEngine", "Animator"));
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, bool)>(charaAnimator->klass, "set_applyRootMotion", 1)->methodPointer(charaAnimator, true);
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, uint64_t)>(charaAnimator->klass, "set_cullingMode", 1)->methodPointer(charaAnimator, 1);
		il2cpp_class_get_method_from_name_type<void (*)(Il2CppObject*, Il2CppObject*)>(charaAnimator->klass, "set_runtimeAnimatorController", 1)->methodPointer(charaAnimator, RuntimeAnimatorController);

		cout << "Character attribute replacement succeeded!" << endl;
	}
	catch (const Il2CppExceptionWrapper& e)
	{
		wcout << "Load Error: " << e.ex->message->chars << endl;
		return false;
	}

	return true;
}

wstring vrmPath;

void* MainManager_Update_orig = nullptr;

static void MainManager_Update_hook(Il2CppObject* self)
{
	reinterpret_cast<decltype(MainManager_Update_hook)*>(MainManager_Update_orig)(self);

	static bool init = false;

	if (!init)
	{
		auto vrmPath = wstring(UnityEngine::PlayerPrefs::GetString(il2cpp_string_new("vrmPath"))->chars);
		if (!vrmPath.empty())
		{
			if (!LoadCharacter(vrmPath))
			{
				UnityEngine::PlayerPrefs::DeleteKey(il2cpp_string_new("vrmPath"));
				UnityEngine::PlayerPrefs::Save();
			}
		}
		init = true;
	}

	if (!vrmPath.empty())
	{
		if (LoadCharacter(vrmPath))
		{
			UnityEngine::PlayerPrefs::TrySetSetString(il2cpp_string_new("vrmPath"), il2cpp_string_new16(vrmPath.data()));
			UnityEngine::PlayerPrefs::Save();

			wcout << "VrmLoaderModule file chosen: " << vrmPath << endl;
		}

		vrmPath.clear();
	}
}

WNDPROC oldWndProcPtr = nullptr;

static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_F4)
		{
			cout << "VrmLoaderModule F4 pressed" << endl;

			thread([]()
				{
					OPENFILENAMEW ofn{};

					ofn.lStructSize = sizeof(ofn);
					ofn.lpstrFilter = L"VRM Files\0*.vrm\0";
					ofn.lpstrFile = new WCHAR[MAX_PATH];
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFileTitle = new WCHAR[64];
					ofn.nMaxFileTitle = 64;
					ofn.lpstrInitialDir = UnityEngine::Application::dataPath()->chars;
					ofn.lpstrTitle = L"Open VRM File";
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

					if (GetOpenFileNameW(&ofn))
					{
						vrmPath = ofn.lpstrFile;
					}
				})
				.detach();
		}
	}

	if (oldWndProcPtr)
	{
		return CallWindowProcW(oldWndProcPtr, hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}

void* ShowWindow_orig = nullptr;

static BOOL WINAPI ShowWindow_hook(
	_In_ HWND hWnd,
	_In_ int nCmdShow)
{
	// Remove from taskbar
	SetWindowLongPtrW(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd, GWL_EXSTYLE) & ~WS_EX_APPWINDOW | WS_EX_TOOLWINDOW);

	oldWndProcPtr = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));

	MH_DisableHook(ShowWindow);
	MH_RemoveHook(ShowWindow);

	return ShowWindow(hWnd, nCmdShow);
}

static void patch_game_assembly()
{
	cout << "Trying to patch GameAssembly.dll..." << endl;

	// il2cpp_dump();

#pragma region HOOK_MACRO
#define ADD_HOOK(_name_, _fmt_) \
	auto _name_##_offset = reinterpret_cast<void*>(_name_##_addr); \
	\
	printf(_fmt_, _name_##_offset); \
	\
	auto _name_##_create_result = MH_CreateHook(_name_##_offset, _name_##_hook, &_name_##_orig); \
	if (_name_##_create_result != MH_OK) \
	{\
		cout << "WARN: " << #_name_ << " Create Failed: " << MH_StatusToString(_name_##_create_result) << endl; \
	}\
	auto _name_##_result = MH_EnableHook(_name_##_offset); \
	if (_name_##_result != MH_OK) \
	{\
		cout << "WARN: " << #_name_ << " Failed: " << MH_StatusToString(_name_##_result) << " LastError: " << GetLastError() << endl << endl; \
		_name_##_orig = _name_##_addr; \
	}
#pragma endregion
#pragma region HOOK_ADDRESSES

	auto MainManager_Update_addr = il2cpp_symbols::get_method_pointer("Assembly-CSharp.dll", "", "MainManager", "Update", 0);

	ADD_HOOK(MainManager_Update, "MainManager::Update: %p\n");
}

bool init_hook()
{
	if (MH_Initialize() != MH_OK)
		return false;

	il2cpp_symbols::load_symbols();

	MH_CreateHook(LoadLibraryW, LoadLibraryW_hook, &LoadLibraryW_orig);
	MH_EnableHook(LoadLibraryW);

	MH_CreateHook(ShowWindow, ShowWindow_hook, &ShowWindow_orig);
	MH_EnableHook(ShowWindow);

	return true;
}

void uninit_hook()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
