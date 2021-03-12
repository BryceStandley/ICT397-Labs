
#include <iostream>
#include <string>
#include <lua/lua.hpp>


bool task2 = false;
bool task3 = false;
bool task4 = false;
bool task5 = false;

int LuaMultiply(int a, int b, int c);

int LuaMultiply(int a, int b, int c)
{
    return a * b * c;
}

int cpp_multiply(lua_State* luaState)
{
    int numParams = lua_gettop(luaState);
    if(numParams < 3)
    {
        std::cout << "Not enough parameters!" << std::endl;
        return 0;
    }
    if(!lua_isnumber(luaState, -1) || !lua_isnumber(luaState, -2) || !lua_isnumber(luaState, -3))
    {
        std::cout << "Bad parameters!" << std::endl;
        return 0;
    }
    int num1 = (int)lua_tonumber(luaState, -1);
    int num2 = (int)lua_tonumber(luaState, -2);
    int num3 = (int)lua_tonumber(luaState, -3);

    int result = LuaMultiply(num1, num2, num3);

    lua_pushnumber(luaState, result);
    return 1;
}

int main()
{
    if (!task2 && !task3 && !task4 && !task5)
    {
        std::cout << "Please toggle each tasks bool to activate them within this file, only one task should be active at one time" << std::endl;
    }

    lua_State* luaState = luaL_newstate();
    if (luaState == NULL)
    {
        std::cout << "Error with Lua Init" << std::endl;
        return 1;
    }


    luaL_openlibs(luaState);

    //Task 2, Load lua script and call function to multiply 
    if (task2)
    {
        luaL_dofile(luaState, "lab03.lua");
        lua_settop(luaState, 0);
        lua_getglobal(luaState, "multiply");
        lua_pushnumber(luaState, 9);
        lua_pushnumber(luaState, 5);
        lua_call(luaState, 2, 1);
    }

    if (task3)
    {
        luaL_dofile(luaState, "script2.lua");
        lua_settop(luaState, 0);
        lua_getglobal(luaState, "levelName");
        lua_getglobal(luaState, "numSectors");
        lua_getglobal(luaState, "numRooms");

        if (lua_isstring(luaState, 1) || lua_isnumber(luaState, 2) || lua_isnumber(luaState, 3))
        {
            std::string scriptString = (std::string)lua_tostring(luaState, 1);
            int sectors = (int)lua_tonumber(luaState, 2);
            int rooms = (int)lua_tonumber(luaState, 3);

            std::cout << scriptString << " has " << sectors << " sectors and " << rooms << " rooms!" << std::endl;
        }

    }

    if (task4)
    {
        int a = 5, b = 6, c = 7;
        luaL_dofile(luaState, "task4.lua");
        lua_settop(luaState, 0);
        lua_getglobal(luaState, "average");
        lua_pushnumber(luaState, a);
        lua_pushnumber(luaState, b);
        lua_pushnumber(luaState, c);
        lua_call(luaState, 3, 1, );

        int result = (int)lua_tonumber(luaState, -1);
        lua_pop(luaState, 1);
        std::cout << "The average of " << a << ", " << b << " and " << c << " is: " << result << std::endl;

    }

    if (task5)
    {
        lua_register(luaState, "cpp_multiply", cpp_multiply);
        luaL_dofile(luaState, "task5.lua");
    }
    

    lua_close(luaState);
    getchar();
    return 0;

}
