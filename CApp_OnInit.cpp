//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }

    if(CArea::AreaControl.OnLoad("./maps/level1.area") == false) {
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if(Player.OnLoad("player.png", 33, 56, 13) == false) {
    	return false;
    }

    CEntity::EntityList.push_back(&Player);

    CEnemy::EnemyList.push_back(new CEnemy(500, 0));
    CEnemy::EnemyList.push_back(new CEnemy(1000, 0));
    CEnemy::EnemyList.push_back(new CEnemy(250, 0));

    for(int i=0; i < CEnemy::EnemyList.size(); i++) {
        if(CEnemy::EnemyList[i]->OnLoad("enemy.png", 34, 47, 3) == false) {
            return false;
        }

        CEntity::EntityList.push_back(CEnemy::EnemyList[i]);
    }

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

    return true;
}

//==============================================================================
