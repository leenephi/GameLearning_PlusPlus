//=============================================================================
#include "CEnemy.h"

// CEnemy::EnemyList[i]->OnLoad("enemy.png", 34, 47, 3);

//=============================================================================

CEnemy::CEnemy(float startX, float startY, char* File, int Width, int Height, int MaxFrames)
{

    X = startX;
    Y = startY;
    OnLoad(File, Width, Height, MaxFrames);

}

//=============================================================================
bool CEnemy::OnLoad(char* File, int Width, int Height, int MaxFrames)
{
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }

    Anim_Control.SetFrameRate(100);
    Anim_Control.Oscillate = true;
    MaxSpeedX = 2;

    return true;
}

//-----------------------------------------------------------------------------
void CEnemy::OnLoop(float playerX, float playerY)
{

    //jumping and chasing mobs
    for(int i = 0; i < CEntity::EntityList.size(); i++)
    {
        // continue with next entity if this one is not an enemy.. for example, a player, who then wouldn't be able to jump
        if(CEntity::EntityList[i]->Type != ENTITY_TYPE_ENEMY) continue;
        CEntity::EntityList[i]->CanJump = false;
        if((playerX - CEntity::EntityList[i]->X < 500) &&
           (CEntity::EntityList[i]->X < playerX) &&
           (abs(CEntity::EntityList[i]->Y) - playerY) < 250)
        {
            if(CEntity::EntityList[i]->MoveRight)
            {
                if(CEntity::EntityList[i]->oldX == CEntity::EntityList[i]->X && CEntity::EntityList[i]->oldY >= CEntity::EntityList[i]->Y)
                {
                    CEntity::EntityList[i]->CanJump = true;
                    CEntity::EntityList[i]->Jump();
                }
            }
            CEntity::EntityList[i]->MoveRight = true;
            CEntity::EntityList[i]->MoveLeft = false;

            CEntity::EntityList[i]->oldX = CEntity::EntityList[i]->X;

            CEntity::EntityList[i]->Anim_Control.Oscillate = true;
        }
        else if((CEntity::EntityList[i]->X - playerX < 500) &&
                (CEntity::EntityList[i]->X > playerX) &&
                (abs(CEntity::EntityList[i]->Y) - playerY) < 250)
        {
            if(CEntity::EntityList[i]->MoveLeft)
            {
                if(CEntity::EntityList[i]->oldX == CEntity::EntityList[i]->X && CEntity::EntityList[i]->oldY >= CEntity::EntityList[i]->Y)
                {
                    CEntity::EntityList[i]->CanJump = true;
                    CEntity::EntityList[i]->Jump();
                }
            }
            CEntity::EntityList[i]->MoveLeft = true;
            CEntity::EntityList[i]->MoveRight = false;

            CEntity::EntityList[i]->oldX = CEntity::EntityList[i]->X;
            CEntity::EntityList[i]->oldY = CEntity::EntityList[i]->Y;

            CEntity::EntityList[i]->Anim_Control.Oscillate = true;


        }
        if((playerX - CEntity::EntityList[i]->X) > 250 || (CEntity::EntityList[i]->X - playerX) > 250)
        {
            CEntity::EntityList[i]->MoveLeft = false;
            CEntity::EntityList[i]->MoveRight = false;
            CEntity::EntityList[i]->Anim_Control.Oscillate = false;

        }
    }

    CEntity::OnLoop(playerX, playerY);

}

//-----------------------------------------------------------------------------
void CEnemy::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 1, CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

//------------------------------------------------------------------------------
void CEnemy::OnCleanup()
{
    CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CEnemy::OnAnimate()
{
    if(SpeedX != 0)
    {
        Anim_Control.MaxFrames = 3;
    }
    else
    {
        Anim_Control.MaxFrames = 0;
    }

    CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CEnemy::OnCollision(CEntity* Entity)
{
    return true;
}

/* void CEnemy::AddEnemy(float x, float y, char* File, int Width, int Height, int MaxFrames) {

    CEnemy* newenemy = new CEnemy(x, y);

    EntityList.push_back(newenemy);

} */

//=============================================================================
