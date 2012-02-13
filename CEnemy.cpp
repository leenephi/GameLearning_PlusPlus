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
    // continue with next entity if this one is not an enemy.. for example, a player, who then wouldn't be able to jump

    CanJump = false;
    if((playerX - X < 500) && (X < playerX) && (abs(Y - playerY) < 250))
    {
        if(MoveRight)
        {
            if(oldX == X && oldY >= Y)
            {
                CanJump = true;
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
    return true;
}

/* void CEnemy::AddEnemy(float x, float y, char* File, int Width, int Height, int MaxFrames) {

    CEnemy* newenemy = new CEnemy(x, y);

    EntityList.push_back(newenemy);

} */

//=============================================================================
