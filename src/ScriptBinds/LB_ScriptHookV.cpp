// =================================================================================
// Includes 
// =================================================================================
#include "Includes.h"
#include "GTALua.h"
#include "lua/Lua.h"
#include "ScriptEngine/ScriptEngine.h"
#include "ScriptBinds.h"
#include "Memory/Memory.h"
#include "thirdparty/ScriptHookV/ScriptHookV.h"

// =================================================================================
// Sleep 
// =================================================================================
void LB_ThreadSleep(UINT s)
{
	ScriptHook::ThreadWait(s);
}

// =================================================================================
// Init Native
// =================================================================================
void LB_InitNative(Natives::NativeReg* pNative)
{
	ScriptHook::InitNative(pNative->hHash);
}

// =================================================================================
// Bind 
// =================================================================================
void ScriptBinds::ScriptHookBind::Bind()
{
	// TODO: Add ability to register own threads
	luabind::module(lua->State(), "scripthookv")
	[
		luabind::def("ThreadSleep", LB_ThreadSleep),
		luabind::def("InitNative", LB_InitNative),
		luabind::def("NativePushInt", ScriptHook::PushValue<int>),
		luabind::def("NativePushFloat", ScriptHook::PushValue<float>),
		luabind::def("NativePushVector", ScriptHook::PushValue<rage::CVector>),
		luabind::def("NativePushBool", ScriptHook::PushValue<bool>),
		luabind::def("NativeCall_GetInt", ScriptHook::Call<int>),
		luabind::def("NativeCall_GetFloat", ScriptHook::Call<float>),
		luabind::def("NativeCall_GetVector", ScriptHook::Call<rage::CVector>),
		luabind::def("NativeCall_GetBool", ScriptHook::Call<bool>)
	];
}