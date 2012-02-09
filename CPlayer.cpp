//=============================================================================
#include "CPlayer.h"

//=============================================================================
CPlayer::CPlayer() {
}

//=============================================================================
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
void CPlayer::OnLoop() {
	CEntity::OnLoop();
}

//-----------------------------------------------------------------------------
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
	if (IsJumping == true) {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + 5) * Height, Width, Height);
	} else {
        CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame() + 6) * Height, Width, Height);
	}
}

//------------------------------------------------------------------------------
void CPlayer::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CPlayer::OnAnimate() {
	/*if(IsJumping == true) {
	    Anim_Control.MaxFrames = 0;
        Anim_Control.CurrentFrame = -1;
	}else
    */
	if(SpeedX != 0) {
		Anim_Control.MaxFrames = 13;
	}else{
		Anim_Control.MaxFrames = 0;
	}

	CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CPlayer::OnCollision(CEntity* Entity) {
    return true;
}

//=============================================================================
