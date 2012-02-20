#include "Weapon.h"

//=============================================================================
Weapon::Weapon()
{
    damage = 50;
    range = 0;
    speed = 0;
    canHit = false;
    X = 100;
    Y = 0;
    Flags = ENTITY_FLAG_MAPONLY;
    hitTimer = 100;
}

//=============================================================================
//bool Weapon::OnLoad(char* File, int Width, int Height, int MaxFrames)
bool Weapon::OnLoad(int Width, int Height)
{
    /*if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }*/
    this->Width = Width;
    this->Height = Height;
    range = Width;
    speed = 2;

    return true;
}

//-----------------------------------------------------------------------------
void Weapon::OnLoop(float playerX, float playerY)
{
    if(canHit == true)
    {
        CEntity::OnLoop(X, Y);
    }

    if(SDL_GetTicks() - onHitTime > hitTimer)
    {
        canHit = false;
        Flags = ENTITY_FLAG_MAPONLY;
    }



}

//-----------------------------------------------------------------------------
void Weapon::OnRender(SDL_Surface* Surf_Display)
{
    /*
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
    if (IsJumping == true)
    {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + 5) * Height, Width, Height);
    }
    else
    {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame() + 6) * Height, Width, Height);
    }
    */
}

//------------------------------------------------------------------------------
void Weapon::OnCleanup()
{
    CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void Weapon::OnAnimate()
{
    /*
    if(SpeedX != 0)
    {
        Anim_Control.MaxFrames = 13;
    }
    else
    {
        Anim_Control.MaxFrames = 0;
    }

    CEntity::OnAnimate();
    */
}

//------------------------------------------------------------------------------
bool Weapon::OnCollision(CEntity* Entity)
{
    if(canHit == true)
    {
        Entity->health -= damage;
        Flags = ENTITY_FLAG_MAPONLY;
        canHit = false;
    }
    return true;
}

//------------------------------------------------------------------------------

void Weapon::DoDamage(float playerX, float playerY, int playerW, int playerH)
{
    canHit = true;
    Flags = ENTITY_FLAG_GHOST;
    onHitTime = SDL_GetTicks();
    X = playerX + playerW;
    Y = (playerY + playerH) - (playerH / 2);
}









