//=============================================================================
#include "CEnemy.h"

// CEnemy::EnemyList[i]->OnLoad("enemy.png", 34, 47, 3);

//=============================================================================

CEnemy::CEnemy(float startX, float startY, char* File, int Width, int Height, int MaxFrames)
{

    X = startX;
    Y = startY;
    damage = 1;
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
    if (Dead)
    {
        X = 0;
        Y = 0;
    }

    CanJump = false;
    MaxSpeedY = 10;
    if((playerX - X < 500) && (X < playerX) && (abs(Y - playerY) < 250))
    {
        if(MoveRight)
        {
            if(oldX == X && oldY >= Y)
            {
                CanJump = true;
                MaxSpeedY = 5;
                Jump();
            }
        }
        MoveRight = true;
        MoveLeft = false;

        oldX = X;

        Anim_Control.Oscillate = true;
    }
    else if((X - playerX < 500) && (X > playerX) && (abs(Y) - playerY) < 250)
    {
        if(MoveLeft)
        {
            if(oldX == X && oldY >= Y)
            {
                CanJump = true;
                MaxSpeedY = 5;
                Jump();
            }
        }
        MoveLeft = true;
        MoveRight = false;

        oldX = X;
        oldY = Y;

        Anim_Control.Oscillate = true;
    }
    if((playerX - X) > 250 || (X - playerX) > 250)
    {
        MoveLeft = false;
        MoveRight = false;
        Anim_Control.Oscillate = false;
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
    if(Y+3 > Entity->Y+Entity->Height)
    {
            Dead = true;
    }
    return true;
}

//=============================================================================
