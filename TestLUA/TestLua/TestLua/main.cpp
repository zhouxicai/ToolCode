#include <iostream>  
#include <string.h>  

using namespace std;

extern "C"
{
#include "lua.h"  
#include "lauxlib.h"  
#include "lualib.h"  
}

static void ReadTableFromItem(lua_State *L, const char* lpszTableName, const char* lpszTableItem)
{
	//printf("it vvv= %d\n", lua_gettop(L));
	int r = lua_getglobal(L, lpszTableName);
	if (r <= 0){
		printf("lua_getglobal return value:%d\n",r);
		lua_pop(L, 2);
		return;
	}
	//printf("it1 = %d\n", lua_gettop(L));

//lua_getglobal(L,"var")会执行两步操作：1.将var放入栈中，2.由Lua去寻找变量var的值，并将变量var的值返回栈顶（替换var）。
//lua_getfield(L,-1,"name")的作用等价于 lua_pushstring(L,"name") + lua_gettable(L,-2) 
#if 0
	lua_pushstring(L, lpszTableItem);
	lua_gettable(L, -2);
#else
	lua_getfield(L, -1, lpszTableItem);
#endif

	if (lua_isnumber(L, -1)) {       //取值输出  
		printf("Is num %s.%s=%d\n", lpszTableName, lpszTableItem, (int)lua_tonumber(L, -1));
	}
	else {
		printf("Is str %s.%s=%s\n", lpszTableName, lpszTableItem, lua_tostring(L, -1));
	}


	lua_pop(L, 2);
}

static void ReadTableFromIndex(lua_State *L, const char* lpszTableName, int index)
{
	int r = lua_getglobal(L, lpszTableName);
	if (r <= 0) {
		printf("lua_getglobal return value:%d\n", r);
		lua_pop(L, 2);
		return;
	}

	printf("it2 = %d\n", lua_gettop(L));

	lua_rawgeti(L, -1, index);

	printf("%s[%d]=%d\n", lpszTableName, index, (int)lua_tonumber(L, -1));

	lua_pop(L, 2);
}

static void EnumTableItem(lua_State *L, const char* lpszTableName)
{
	int r = lua_getglobal(L, lpszTableName);
	if (r <= 0) {
		printf("lua_getglobal return value:%d\n", r);
		lua_pop(L, 2);
		return;
	}

	int it = lua_gettop(L);

	printf("it = %d\n", it);

	lua_pushnil(L);

	printf("Enum %s:", lpszTableName);

	while (lua_next(L, it))
	{		
		if (lua_isnumber(L, -1)) {  
			printf("  %d", (int)lua_tonumber(L, -1));
		}
		else {
			printf("  %s", lua_tostring(L, -1));
		}
		lua_pop(L, 1);
	}

	printf("\n");

	lua_pop(L, 1);
}

#if 0
int main(int argc, char* argv[])
{
	lua_State *L = luaL_newstate();

	printf("LuaTable = %d\n", lua_gettop(L));

	luaopen_base(L);

	printf("LuaTable = %d\n", lua_gettop(L));

	luaL_dofile(L, "LuaTable.lua");

	printf("LuaTable = %d\n", lua_gettop(L));

	ReadTableFromItem(L, "luatb1", "a");  // 等价与lua代码：print(luat_Test1.a)
	ReadTableFromItem(L, "luatb1", "b");
	ReadTableFromItem(L, "luatb1", "c");

	EnumTableItem(L, "luatb1");    // 枚举Table

	ReadTableFromIndex(L, "luatb2", 1);  // 等价与lua代码：print(luat_Test1[1])
	ReadTableFromIndex(L, "luatb2", 2);
	ReadTableFromIndex(L, "luatb2", 3);

	EnumTableItem(L, "luatb2");

	lua_close(L);

	getchar();

	return 0;
}
#endif


#if 1
void main()
{

	//1.创建Lua状态  
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return;
	}



	//2.加载Lua文件  
	int bRet = luaL_loadfile(L, "hello.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		return;
	}



	//3.运行Lua文件  
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		cout << "pcall error" << endl;
		return;
	}



	//4.读取变量  
	lua_getglobal(L, "str");
	string str = lua_tostring(L, -1);
	cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

	lua_getglobal(L, "num");
	int num = lua_tointeger(L, -1);
	cout << "num = " << num << endl;   

	//5.读取table  
	lua_getglobal(L, "tbl");
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	cout << "tbl:name = " << str.c_str() << endl; //tbl:name = shun  



    //6.读取函数  
	lua_getglobal(L, "add");        // 获取函数，压入栈中  
	lua_pushnumber(L, 10);          // 压入第一个参数  
	lua_pushnumber(L, 20);          // 压入第二个参数  
	int iRet = lua_pcall(L, 2, 1, 0);// 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。  

	if (iRet)                       // 调用出错  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		return;
	}

	if (lua_isnumber(L, -1))        //取值输出  
	{
		double fValue = lua_tonumber(L, -1);
		cout << "lua calculate 10 plus 20 Result is " << fValue << endl;
	}



	//至此，栈中的情况是：  
	//=================== 栈顶 ===================   
	//  索引  类型      值  
	//   4   int：      30   
	//   3   string：   shun   
	//   2   table:     tbl  
	//   1   string:    I am so cool~  
	//=================== 栈底 ===================   

	//7.关闭state  
	lua_close(L);
	while (1)
	{
	}
	return;

}
#endif
