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

//lua_getglobal(L,"var")��ִ������������1.��var����ջ�У�2.��LuaȥѰ�ұ���var��ֵ����������var��ֵ����ջ�����滻var����
//lua_getfield(L,-1,"name")�����õȼ��� lua_pushstring(L,"name") + lua_gettable(L,-2) 
#if 0
	lua_pushstring(L, lpszTableItem);
	lua_gettable(L, -2);
#else
	lua_getfield(L, -1, lpszTableItem);
#endif

	if (lua_isnumber(L, -1)) {       //ȡֵ���  
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

	ReadTableFromItem(L, "luatb1", "a");  // �ȼ���lua���룺print(luat_Test1.a)
	ReadTableFromItem(L, "luatb1", "b");
	ReadTableFromItem(L, "luatb1", "c");

	EnumTableItem(L, "luatb1");    // ö��Table

	ReadTableFromIndex(L, "luatb2", 1);  // �ȼ���lua���룺print(luat_Test1[1])
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

	//1.����Lua״̬  
	lua_State *L = luaL_newstate();
	if (L == NULL)
	{
		return;
	}



	//2.����Lua�ļ�  
	int bRet = luaL_loadfile(L, "hello.lua");
	if (bRet)
	{
		cout << "load file error" << endl;
		return;
	}



	//3.����Lua�ļ�  
	bRet = lua_pcall(L, 0, 0, 0);
	if (bRet)
	{
		cout << "pcall error" << endl;
		return;
	}



	//4.��ȡ����  
	lua_getglobal(L, "str");
	string str = lua_tostring(L, -1);
	cout << "str = " << str.c_str() << endl;        //str = I am so cool~  

	lua_getglobal(L, "num");
	int num = lua_tointeger(L, -1);
	cout << "num = " << num << endl;   

	//5.��ȡtable  
	lua_getglobal(L, "tbl");
	lua_getfield(L, -1, "name");
	str = lua_tostring(L, -1);
	cout << "tbl:name = " << str.c_str() << endl; //tbl:name = shun  



    //6.��ȡ����  
	lua_getglobal(L, "add");        // ��ȡ������ѹ��ջ��  
	lua_pushnumber(L, 10);          // ѹ���һ������  
	lua_pushnumber(L, 20);          // ѹ��ڶ�������  
	int iRet = lua_pcall(L, 2, 1, 0);// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  

	if (iRet)                       // ���ó���  
	{
		const char *pErrorMsg = lua_tostring(L, -1);
		cout << pErrorMsg << endl;
		lua_close(L);
		return;
	}

	if (lua_isnumber(L, -1))        //ȡֵ���  
	{
		double fValue = lua_tonumber(L, -1);
		cout << "lua calculate 10 plus 20 Result is " << fValue << endl;
	}



	//���ˣ�ջ�е�����ǣ�  
	//=================== ջ�� ===================   
	//  ����  ����      ֵ  
	//   4   int��      30   
	//   3   string��   shun   
	//   2   table:     tbl  
	//   1   string:    I am so cool~  
	//=================== ջ�� ===================   

	//7.�ر�state  
	lua_close(L);
	while (1)
	{
	}
	return;

}
#endif
