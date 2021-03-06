//=============================================================================
#include "CPlayer.h"

//=============================================================================
CPlayer::CPlayer()
{
    armed = false;
    onHitTime = 0;
    health = 100;
    range = 10;
    canAttack = true;
    hitTimer = 500;
    currentItem = NULL;
    Flags = ENTITY_FLAG_MAPONLY | ENTITY_FLAG_GRAVITY;
}

CPlayer::~CPlayer()
{
    OnCleanup();
}


//=============================================================================
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames)
{
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
void CPlayer::OnLoop(float playerX, float playerY)
{

    if(health < 1)
    {
        health = 100;
        X = 0;
        Y = 50;
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


    CEntity::OnLoop(X, Y);

}

//-----------------------------------------------------------------------------
void CPlayer::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    if (IsJumping == true)
    {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + 5) * Height, Width, Height);
    }
    else
    {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame() + 6) * Height, Width, Height);
    }
}

//------------------------------------------------------------------------------
void CPlayer::OnCleanup()
{
    CEntity::OnCleanup();
    if(armed)
    {
        currentItem->OnCleanup();
    }
}

//------------------------------------------------------------------------------
void CPlayer::OnAnimate()
{
    if(SpeedX != 0)
    {
        Anim_Control.MaxFrames = 13;
    }
    else
    {
        Anim_Control.MaxFrames = 0;
    }

    CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CPlayer::OnCollision(CEntity* Entity)
{
    if(Entity->Type == ENTITY_TYPE_WEAPON)
    {
        Wield(Entity);
    }
    return true;
}

//=============================================================================

void CPlayer::Attack()
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

void CPlayer::TakeDamage(int damage)
{
    health -= damage;
}

//=============================================================================

void CPlayer::Wield(CEntity* itemToWield)
{
    if(armed) return;
    armed = true;
    itemToWield->SetOwner(this);
    currentItem = itemToWield;
}

//=============================================================================











