#ifndef CSCREENTEXT_H_INCLUDED
#define CSCREENTEXT_H_INCLUDED

#include "SDL_ttf.h"
#include "CSurface.h"

class CScreenText
{

public:
    static CScreenText  ScreenTextControl;

//The color of the font SDL_Color textColor = { 255, 255, 255 };

private:
    SDL_Surface*	Surf_Text;

    TTF_Font*       font;

    SDL_Color       textColor;

    char health[50];

    char testing[100];

public:
    CScreenText();

    bool OnLoad();

    const void OnLoop();

    void OnRender(SDL_Surface* Surf_Display, int playerHealth, bool canAttack);

    void OnCleanup();
};

#endif // CSCREENTEXT_H_INCLUDED
