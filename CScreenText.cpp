
#include "CScreenText.h"
#include "CAppStateGame.h"



CScreenText CScreenText::ScreenTextControl;

CScreenText::CScreenText()
{
    Surf_Text = NULL;
    font = NULL;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
}



bool CScreenText::OnLoad()
{
OnCleanup();
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
    Surf_Text = NULL;

    // The following is to see test stuff on the screen.. for testing!

    sprintf(testing, "Objects: %d", CEntity::EntityList.size());

    Surf_Text = TTF_RenderText_Solid(font, testing, textColor);
    CSurface::OnDraw(Surf_Display, Surf_Text, 0, 20);
    SDL_FreeSurface(Surf_Text);
    Surf_Text = NULL;
}

void CScreenText::OnCleanup()
{
    SDL_FreeSurface(Surf_Text);
    Surf_Text = NULL;
    TTF_CloseFont(font);
    font = NULL;

}
