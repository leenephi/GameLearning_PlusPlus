#include "CAppStateIntro.h"

#include "CAppStateManager.h"

CAppStateIntro CAppStateIntro::Instance;

CAppStateIntro::CAppStateIntro()
{
    Surf_Logo = NULL;
}

void CAppStateIntro::OnActivate()
{
    // Load Simple Logo
    Surf_Logo = CSurface::OnLoad("splash.png");

    StartTime = SDL_GetTicks();
}

void CAppStateIntro::OnDeactivate()
{
    if(Surf_Logo)
    {
        SDL_FreeSurface(Surf_Logo);
        Surf_Logo = NULL;
    }
}

void CAppStateIntro::OnLoop()
{
    if(StartTime + 1000 < SDL_GetTicks())
    {
        CAppStateManager::SetActiveAppState(APPSTATE_MENU);
    }
}

void CAppStateIntro::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Logo)
    {
        CSurface::OnDraw(Surf_Display, Surf_Logo, 0, 0);
    }
}

CAppStateIntro* CAppStateIntro::GetInstance()
{
    return &Instance;
}
