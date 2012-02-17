
#include "CScreenText.h"



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

void CScreenText::OnLoop()
{

}

void CScreenText::OnRender(SDL_Surface* Surf_Display, int playerHealth)
{
    char health[50];
    sprintf(health, "Health: %d", playerHealth);

    Surf_Text = TTF_RenderText_Solid(font, health, textColor);
    CSurface::OnDraw(Surf_Display, Surf_Text, 0, 0);
}

void CScreenText::OnCleanup()
{
    SDL_FreeSurface(Surf_Text);
    TTF_CloseFont(font);
    TTF_Quit();
}
