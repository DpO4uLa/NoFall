#include "main.h"

using CAnimManager_BlendAnimation_t = void* (__cdecl*)(void*, int, int, float);

std::unique_ptr<memwrapper::memhook<CAnimManager_BlendAnimation_t>> pCAnimManager_BlendAnimation;

void* __cdecl CAnimManager_BlendAnimation_HOOKED(void* clump, int AssocGroupId, int AnimationId, float clumpAssocBlendData) {

	if (AssocGroupId == 0 && AnimationId == 120) {
		AnimationId = 1;
		clumpAssocBlendData = 5;
	}

	return pCAnimManager_BlendAnimation->call<void*, int, int, float>(clump, AssocGroupId, AnimationId, clumpAssocBlendData);
}

int __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH: {
			pCAnimManager_BlendAnimation = std::make_unique<memwrapper::memhook<CAnimManager_BlendAnimation_t>>(0x004D4610U, CAnimManager_BlendAnimation_HOOKED);
			pCAnimManager_BlendAnimation->install();
			break;
		}
		case DLL_PROCESS_DETACH: {
			pCAnimManager_BlendAnimation->remove();
			break;
		}	
	}
	return true;
}