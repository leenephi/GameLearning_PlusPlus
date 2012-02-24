//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup()
{
    CAppStateManager::SetActiveAppState(APPSTATE_NONE);

    SDL_FreeSurface(Surf_Display);
    Surf_Display = NULL;
    TTF_Quit();
    SDL_Quit();
}

//==============================================================================
