
#include "CScreenText.h"
#include "CAppStateGame.h"



CScreenText CScreenText::ScreenTextControl;

CScreenText::CScreenText()
{
    Surf_Text = NULL;
    font = NULL;
    textColor = {255, 255, 255 };
}



bool CScreenText::OnLoad()
{
    font = TTF_OpenFont( "FOO.ttf", 28 );
    if(font == NULL)
    {
        return false;
    }
}

const void CScreenText::OnLoop()
{

}

void CScreenText::OnRender(SDL_Surface* Surf_Display, int playerHealth, bool canAttack)
{
    sprintf(health, "Health: %d", playerHealth);

    Surf_Text = TTF_RenderText_Solid(font, health, textColor);
    CSurface::OnDraw(Surf_Display, Surf_Text, 0, 0);
    SDL_FreeSurface(Surf_Text);

    // The following is to see test stuff on the screen.. for testing!

    if (canAttack == true)
    {
        sprintf(testing, "Can attack: true");
    }
    else
    {
        sprintf(testing, "Can attack: false");
    }
    Surf_Text = TTF_RenderText_Solid(font, testing, textColor);
    CSurface::OnDraw(Surf_Display, Surf_Text, 0, 20);
    SDL_FreeSurface(Surf_Text);
}

void CScreenText::OnCleanup()
{
    SDL_FreeSurface(Surf_Text);
    TTF_CloseFont(font);
    TTF_Quit();
}
