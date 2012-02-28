//=============================================================================
#include "CEnemy.h"

// CEnemy::EnemyList[i]->OnLoad("enemy.png", 34, 47, 3);

//=============================================================================

CEnemy::CEnemy(float startX, float startY, char* File, int Width, int Height, int MaxFrames)
{
    armed = false;
    canAttack = true;
    hitTimer = 1500;
    onHitTime = 0;
    X = startX;
    Y = startY;
    health = 100;
    currentItem = NULL;
    OnLoad(File, Width, Height, MaxFrames);
    Type = ENTITY_TYPE_ENEMY;
    Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_MAPONLY;

}

CEnemy::~CEnemy()
{
    OnCleanup();
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

    if (health < 1)
    {
        X = 0;
        Y = 0;
        Dead = true;
    }

    if(SDL_GetTicks() - onHitTime > hitTimer)
    {
        canAttack = true;
    }


    // Give the coordinates to the equiped items; weapon in this case
    if(armed)
    {
        //if facing right, face the item right
        if(CurrentFrameCol == 0)
        {
            currentItem->X = X + Width;
            currentItem->SetCurrentFrameCol(0);
        }
        //if facing left, face the item left
        else if(CurrentFrameCol == 1)
        {
            currentItem->X = X - currentItem->Width;
            currentItem->SetCurrentFrameCol(1);
        }

        currentItem->Y = (Y + Height) - (Height / 2);
    }

    // Have the enemy start attacking if close enough

    if((armed) && (canAttack) && (abs(X - playerX) < 75) && (abs(Y - playerY) < 25))
    {
        Jump();
        Attack();
    }

    // Have the enemy chase the player within a certain range
    // Enemy attempts to jump if chasing and can't move

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
    if(armed)
    {
        currentItem->OnCleanup();
    }
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

//=============================================================================

void CEnemy::Attack()
{
    if(armed)
    {
        if(canAttack == false)
        {
            return;
        }

        canAttack = false;
        onHitTime = SDL_GetTicks();
        currentItem->DoDamage();
    }
}

//=============================================================================

void CEnemy::Wield(CEntity* itemToWield)
{
    armed = true;
    itemToWield->used = true;
    itemToWield->SetOwner(this);
    currentItem = itemToWield;
}
