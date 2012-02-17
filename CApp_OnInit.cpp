//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if( TTF_Init() == -1 )
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    SDL_WM_SetCaption("GameLearning", "PlusPlus");

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    CAppStateManager::SetActiveAppState(APPSTATE_INTRO);


    return true;

}

//==============================================================================
