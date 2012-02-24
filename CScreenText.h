#ifndef CSCREENTEXT_H_INCLUDED
#define CSCREENTEXT_H_INCLUDED

#include <SDL_ttf.h>
#include "CSurface.h"

class CScreenText
{

public:
    static CScreenText  ScreenTextControl;

    char health[50];

    char testing[100];

private:
    SDL_Surface*	Surf_Text;

    TTF_Font*       font;

    SDL_Color       textColor;

public:
    CScreenText();

    bool OnLoad();

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display, int playerHealth, bool canAttack);

    void OnCleanup();
};

#endif // CSCREENTEXT_H_INCLUDED
