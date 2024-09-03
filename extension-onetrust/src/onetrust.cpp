#define LIB_NAME "OneTrust"
#define MODULE_NAME "onetrust"

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "onetrust_private.h"

namespace dmOneTrust {

static int Init(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"init", Init},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeOneTrust(dmExtension::AppParams* params)
{
    dmLogInfo("AppInitializeonetrust");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeOneTrust(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    Initialize_Ext(params);
    dmLogInfo("Registered %s Extension", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeOneTrust(dmExtension::AppParams* params)
{
    dmLogInfo("AppFinalizeOneTrust");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeOneTrust(dmExtension::Params* params)
{
    dmLogInfo("FinalizeOneTrust");
    return dmExtension::RESULT_OK;
}

} //namespace dmOneTrust

DM_DECLARE_EXTENSION(OneTrust, LIB_NAME, dmOneTrust::AppInitializeOneTrust, dmOneTrust::AppFinalizeOneTrust, dmOneTrust::InitializeOneTrust, 0, 0, dmOneTrust::FinalizeOneTrust)

#else

static  dmExtension::Result InitializeOneTrust(dmExtension::Params* params)
{
    dmLogInfo("Registered extension OneTrust (null)");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeOneTrust(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeOneTrust, 0, 0, FinalizeOneTrust)

#endif // IOS/Android
