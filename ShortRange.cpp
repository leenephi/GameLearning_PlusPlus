#include "ShortRange.h"

//=============================================================================
ShortRange::ShortRange()
{
    damage = 0;
    range = 0;
    speed = 0;
}

//=============================================================================
bool ShortRange::OnLoad(char* File, int Width, int Height, int MaxFrames)
{
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false)
    {
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
void ShortRange::OnLoop()
{
    CEntity::OnLoop(X, Y);
}

//-----------------------------------------------------------------------------
void ShortRange::OnRender(SDL_Surface* Surf_Display)
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
void ShortRange::OnCleanup()
{
    CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void ShortRange::OnAnimate()
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
bool ShortRange::OnCollision(CEntity* Entity)
{
    return true;
}
