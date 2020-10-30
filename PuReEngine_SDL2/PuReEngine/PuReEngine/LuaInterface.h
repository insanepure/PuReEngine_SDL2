#pragma once

#ifdef __linux__
//LINUX
extern "C" {
#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>
}
#elif _WIN32
//Windows
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#elif _APPLE_
#include "TargetConditionals.h"
#ifdef TARGET_OS_MAC
//MAC
#endif
#endif



namespace PuRe
{
	class LuaInterface
	{
	public:
		LuaInterface(const char *file);
		void PushFunction(lua_CFunction function);
		void RegisterFunction(const char* name);
		void UseFunction(const char* name);
		void AddFloat(float Num);
		void AddInt(int Num);
		void AddBoolean(bool Num);
		void CallFunction(int results);
		int PCallFunction(int results);
		float GetFloat(int index);
		int GetInt(int index);
		bool GetBoolean(int index);
		void EndFunction();
		lua_State *L;
		~LuaInterface();
	private:
		int arguments;
	};
}
