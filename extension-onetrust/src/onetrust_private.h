#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#pragma once

#include <dmsdk/sdk.h>

namespace dmOneTrust {


void Initialize_Ext(dmExtension::Params* params);
void Finalize_Ext();

void Initialize();


} //namespace dmOneTrust

#endif
