#include "LuaInterface.h"

namespace PuRe
{
	LuaInterface::LuaInterface(const char* file)
	{
		this->arguments = 0;
		this->L = luaL_newstate();
		luaL_openlibs(this->L);
		/* load the script */
		luaL_dofile(this->L, file);
	}
	void LuaInterface::PushFunction(lua_CFunction function)
	{
		lua_pushcfunction(this->L,function);
	}
	void LuaInterface::AddFloat(float number)
	{
		lua_pushnumber(this->L, number);
		this->arguments++;
	}
	void LuaInterface::RegisterFunction(const char* name)
	{
		lua_setglobal(this->L, name);
	}
	void LuaInterface::AddInt(int number)
	{
		lua_pushnumber(this->L, number);
		this->arguments++;
	}
	void LuaInterface::AddBoolean(bool number)
	{
		lua_pushboolean(this->L, number);
		this->arguments++;
	}
	bool LuaInterface::GetBoolean(int index)
	{
		return lua_toboolean(this->L, index) == 1;
	}
	int LuaInterface::GetInt(int index)
	{
		return (int)lua_tonumber(this->L, index);
	}
	float LuaInterface::GetFloat(int index)
	{
		return (float)lua_tonumber(this->L, index);
	}
	void LuaInterface::CallFunction(int results)
	{
		lua_call(L, this->arguments, results);
	}
	int LuaInterface::PCallFunction(int results)
	{
		return lua_pcall(L, this->arguments, results,0);
	}
	void LuaInterface::UseFunction(const char* name)
	{
		lua_settop(L,0);
		lua_getglobal(L, name);
	}
	void LuaInterface::EndFunction()
	{
		this->arguments = 0;
		lua_pop(L, 1);
	}
	LuaInterface::~LuaInterface()
	{
		lua_close(this->L);
	}
}