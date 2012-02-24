//=============================================================================
#include "CPlayer.h"

//=============================================================================
CPlayer::CPlayer()
{
    onHitTime = 0;
    health = 100;
    damage = 10;
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

    if(health < 0)
    {
        health = 100;
        X = 0;
        Y = 50;
    }

    if(SDL_GetTicks() - onHitTime > hitTimer)
    {
        canAttack = true;
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
}

//------------------------------------------------------------------------------
void CPlayer::OnAnimate()
{
    /*if(IsJumping == true) {
        Anim_Control.MaxFrames = 0;
        Anim_Control.CurrentFrame = -1;
    }else
    */
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
    if (Entity->Type == ENTITY_TYPE_ENEMY)
    {
        if(!(Entity->Y+3 > Y + Height))
        {
            TakeDamage(Entity->damage);
        }
    }

    return true;
}

//=============================================================================

void CPlayer::Attack()
{
    if(canAttack == false)
    {
        return;
    }

    canAttack = false;
    onHitTime = SDL_GetTicks();
    currentItem->DoDamage(X, Y, Width, Height);
}

//=============================================================================

void CPlayer::TakeDamage(int damage)
{
    health -= damage;
}

//=============================================================================

void CPlayer::Wield(Weapon* itemToWield)
{
    currentItem = itemToWield;
}











