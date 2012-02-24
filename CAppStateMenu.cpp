#include "CAppStateMenu.h"

#include "CAppStateManager.h"

#include "CAppStateGame.h"

CAppStateMenu CAppStateMenu::Instance;

CAppStateMenu::CAppStateMenu()
{
    Surf_Menu = NULL;
}

void CAppStateMenu::OnActivate()
{

    // Load Simple Menu
    Surf_Menu = CSurface::OnLoad("menu.png");
    start_game = false;
}

void CAppStateMenu::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{

    switch(sym)
    {
    case SDLK_RETURN:
    {
        start_game = true;
        break;
    }
    default:
    {

    }
    }
}

void CAppStateMenu::OnDeactivate()
{
    if(Surf_Menu)
    {
        SDL_FreeSurface(Surf_Menu);
        Surf_Menu = NULL;
    }
}

void CAppStateMenu::OnLoop()
{
    if(start_game)
    {
        CAppStateManager::SetActiveAppState(APPSTATE_GAME);
    }
}

void CAppStateMenu::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Menu)
    {
        CSurface::OnDraw(Surf_Display, Surf_Menu, 0, 0);
    }
}

CAppStateMenu* CAppStateMenu::GetInstance()
{
    return &Instance;
}

