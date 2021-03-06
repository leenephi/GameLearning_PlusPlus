#include "Weapon.h"

//=============================================================================
Weapon::Weapon()
{
    onHitTime = 0;
    damage = 10;
    range = 0;
    speed = 0;
    canHit = false;
    used = false;
    X = 0;
    Y = 0;
    Type = ENTITY_TYPE_WEAPON;
    Flags = ENTITY_FLAG_MAPONLY | ENTITY_FLAG_GRAVITY;
    hitTimer = 100;
}
Weapon::~Weapon()
{
        OnCleanup();
}
//=============================================================================
//bool Weapon::OnLoad(char* File, int Width, int Height, int MaxFrames)
bool Weapon::OnLoad(char* File, int Width, int Height)
{
    if(CEntity::OnLoad(File, Width, Height, 1) == false)
    {
        return false;
    }
    this->Width = Width;
    this->Height = Height;
    range = Width;
    speed = 2;

    return true;
}

//-----------------------------------------------------------------------------
void Weapon::OnLoop(float playerX, float playerY)
{
    if(used)
    {
        Flags = ENTITY_FLAG_GHOST;

        if(SDL_GetTicks() - onHitTime > hitTimer)
        {
            canHit = false;
        }
    }

    CEntity::OnLoop(X, Y);
}

//-----------------------------------------------------------------------------
void Weapon::OnRender(SDL_Surface* Surf_Display)
{
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width, CurrentFrameRow * Height, Width, Height);
}

//------------------------------------------------------------------------------
void Weapon::OnCleanup()
{
    CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void Weapon::OnAnimate()
{
    CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool Weapon::OnCollision(CEntity* Entity)
{
    if((canHit == true) && Owner != Entity)
    {
        Entity->health -= damage;
        Entity->KnockBack();
        Flags = ENTITY_FLAG_MAPONLY;
        canHit = false;
    }
    return true;
}

//------------------------------------------------------------------------------

void Weapon::DoDamage()
{
    canHit = true;
    Flags = ENTITY_FLAG_MAPONLY;
    onHitTime = SDL_GetTicks();
}

//------------------------------------------------------------------------------

void Weapon::SetOwner(CEntity* Entity)
{
    Owner = Entity;
    used = true;
}

//------------------------------------------------------------------------------

void Weapon::OnDrop()
{
    Owner = NULL;
    used = false;
    Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_MAPONLY;
    //KnockBack();
}








