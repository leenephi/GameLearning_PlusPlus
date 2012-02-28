#include "CAppStateGame.h"
#include "CAppStateManager.h"
#include <cmath>

CAppStateGame CAppStateGame::Instance;

CAppStateGame::CAppStateGame()
{
}

void CAppStateGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{

    switch(sym)
    {
    case SDLK_a:
    {
        Player.MoveLeft = true;
        break;
    }

    case SDLK_d:
    {
        Player.MoveRight = true;
        break;
    }

    case SDLK_SPACE:
    {
        Player.Jump();
        Player.IsJumping = true;
        break;
    }
    case SDLK_ESCAPE:
    {

        Reset();
        CAppStateManager::SetActiveAppState(APPSTATE_MENU);

        break;
    }
    case SDLK_p:
    {
        if(timer + 200 < SDL_GetTicks())
        {
            timer = SDL_GetTicks();



            if(!pause) pause = true;

            else
            {
                pause = false;
                break;
            }
        }
        break;
    }
    default:
    {
    }
    }
}

//------------------------------------------------------------------------------
void CAppStateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_a:
    {
        Player.MoveLeft = false;
        break;
    }

    case SDLK_d:
    {
        Player.MoveRight = false;
        break;
    }

    default:
    {
    }
    }
}

void CAppStateGame::OnLButtonDown(int mX, int mY)
{
    Player.Attack();
}

/*
/
/   -------------------------------------------
/
/   ON ACTIVATE FOOL DONT GET LOST IN THIS CODE
/
/   -------------------------------------------
/
*/


void CAppStateGame::OnActivate()
{
    pause = false;
    timer = 0;
    Surf_Pause = CSurface::OnLoad("splash.png");
    CArea::AreaControl.OnLoad("./maps/savearea.area");
    CScreenText::ScreenTextControl.OnLoad();

    Player.OnLoad("player.png", 33, 56, 13);
    Player.Type = ENTITY_TYPE_PLAYER;

    Weapon* TestWeapon = new Weapon;
    TestWeapon->OnLoad("dagger.png", 16, 16);
    TestWeapon->X = 75;
    CEntity::EntityList.push_back(TestWeapon);

    CEntity::EntityList.push_back(&Player);

    CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(0,0);//(&Player.X, &Player.Y);
}

void CAppStateGame::OnDeactivate()
{


    CArea::AreaControl.OnCleanup();
    CScreenText::ScreenTextControl.OnCleanup();

    for(int i = 0; i < CEntity::EntityList.size(); i++)
    {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnCleanup();
    }

    SDL_FreeSurface(Surf_Pause);
    Surf_Pause = NULL;


    CEntity::EntityList.clear();


}

void CAppStateGame::OnLoop()
{
    if(pause)
    {
        return;
    }
    else
    {

        //--------------------------------------------------------------------------
        // Entities
        //--------------------------------------------------------------------------
        for(int i = 0; i < CEntity::EntityList.size(); i++)
        {
            if(!CEntity::EntityList[i]) continue;

            CEntity::EntityList[i]->OnLoop(Player.X, Player.Y);
        }

        //Collision Events
        for(int i = 0; i < CEntityCol::EntityColList.size(); i++)
        {
            CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
            CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

            if(EntityA == NULL || EntityB == NULL) continue;

            if(EntityA->OnCollision(EntityB))
            {
                EntityB->OnCollision(EntityA);
            }
        }
        CEntityCol::EntityColList.clear();
    }
}

void CAppStateGame::OnRender(SDL_Surface* Surf_Display)
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WWIDTH;
    Rect.h = WHEIGHT;

    SDL_FillRect(Surf_Display, &Rect, 0);
    if(pause)
    {
        CSurface::OnDraw(Surf_Display, Surf_Pause, 0, 0);
    }
    else
    {
        CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
        CScreenText::ScreenTextControl.OnRender(Surf_Display, Player.health, Player.canAttack);

        //--------------------------------------------------------------------------
        // Entities
        //--------------------------------------------------------------------------
        for(int i = 0; i < CEntity::EntityList.size(); i++)
        {
            if(!CEntity::EntityList[i]) continue;

            CEntity::EntityList[i]->OnRender(Surf_Display);
        }
    }
}


CAppStateGame* CAppStateGame::GetInstance()
{
    return &Instance;
}


void CAppStateGame::Reset()
{
    Player.IsJumping = false;
    Player.MoveLeft = false;
    Player.MoveRight = false;
    Player.X = 0;
    Player.Y = 0;
}
