#ifndef __CAPPSTATEGAME_H__
#define __CAPPSTATEGAME_H__

#include "CAppState.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CSurface.h"
#include "CScreenText.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "Item.h"
#include "Weapon.h"

class CAppStateGame : public CAppState
{
private:

private:
            CAppStateGame();

    bool    pause;

public:
    static  CAppStateGame Instance;

    CPlayer	Player;

    void    OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void    OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

    void    OnLButtonDown(int mX, int mY);

public:
    void    OnActivate();

    void    OnDeactivate();

    void    OnLoop();

    void    OnRender(SDL_Surface* Surf_Display);

    void    Reset();

public:
    static  CAppStateGame* GetInstance();
};

#endif
