//=============================================================================
#include "CEnemy.h"

//=============================================================================

std::vector<CEnemy*> 	CEnemy::EnemyList;

CEnemy::CEnemy(float x, float y) {

    X = x;
    Y = y;

}

//=============================================================================
bool CEnemy::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {
        return false;
    }

    Anim_Control.SetFrameRate(100);
    Anim_Control.Oscillate = true;
    MaxSpeedX = 3;
    X = 500;

    return true;
}

//-----------------------------------------------------------------------------
void CEnemy::OnLoop() {

	CEntity::OnLoop();

}

//-----------------------------------------------------------------------------
void CEnemy::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;
	CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 1, CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

//------------------------------------------------------------------------------
void CEnemy::OnCleanup() {
	CEntity::OnCleanup();
}

//------------------------------------------------------------------------------
void CEnemy::OnAnimate() {
	if(SpeedX != 0) {
		Anim_Control.MaxFrames = 3;
	}else{
		Anim_Control.MaxFrames = 0;
	}

	CEntity::OnAnimate();
}

//------------------------------------------------------------------------------
bool CEnemy::OnCollision(CEntity* Entity) {
    return true;
}

void CEnemy::AddEnemy(float x, float y) {

    CEnemy* newenemy = new CEnemy(x, y);

    EnemyList.push_back(newenemy);

}

//=============================================================================
