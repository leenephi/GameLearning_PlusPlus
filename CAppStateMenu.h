#ifndef __CAPPSTATEMENU_H__
#define __CAPPSTATEMENU_H__

#include "CAppState.h"
#include "CSurface.h"

class CAppStateMenu : public CAppState
{
private:
    static CAppStateMenu Instance;

    SDL_Surface* Surf_Menu;

    bool start_game;

private:
    CAppStateMenu();

public:
    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnActivate();

    void OnDeactivate();

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

public:
    static CAppStateMenu* GetInstance();
};

#endif
