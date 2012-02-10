#include "CAppStateGame.h"

CAppStateGame CAppStateGame::Instance;

CAppStateGame::CAppStateGame() {
}

void CAppStateGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

	switch(sym) {
		case SDLK_a: {
			Player.MoveLeft = true;
			break;
		}

		case SDLK_d: {
			Player.MoveRight = true;
			break;
		}

		case SDLK_SPACE: {
		    Player.Jump();
		    Player.IsJumping = true;
		    break;
		}

		default: {
		}
	}
}

//------------------------------------------------------------------------------
void CAppStateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_a: {
			Player.MoveLeft = false;
			break;
		}

		case SDLK_d: {
			Player.MoveRight = false;
			break;
		}

		default: {
		}
	}
}

void CAppStateGame::AddEnemy(float x, float y) {

        CEnemy* newenemy = new CEnemy(x, y);

        CEnemy::EnemyList.push_back(newenemy);

}

void CAppStateGame::OnActivate() {
    CArea::AreaControl.OnLoad("./maps/level1.area");

    Player.OnLoad("player.png", 33, 56, 13);

    CEntity::EntityList.push_back(&Player);

    AddEnemy(500, 0);

    AddEnemy(600, 0);


    for(int i=0; i < CEnemy::EnemyList.size(); i++) {

        CEnemy::EnemyList[i]->OnLoad("enemy.png", 34, 47, 3);

        CEntity::EntityList.push_back(CEnemy::EnemyList[i]);
    }

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
    CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
}

void CAppStateGame::OnDeactivate() {
    CArea::AreaControl.OnCleanup();

    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnCleanup();
    }

    CEntity::EntityList.clear();
}

void CAppStateGame::OnLoop() {
    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }
    //jumping mob

    for(int i = 0; i < CEnemy::EnemyList.size(); i++) {
        CEnemy::EnemyList[i]->CanJump = false;
        if((Player.X - CEnemy::EnemyList[i]->X < 500) && CEnemy::EnemyList[i]->X < Player.X) {
            if(CEnemy::EnemyList[i]->MoveRight)
            {
                if(CEnemy::EnemyList[i]->oldX == CEnemy::EnemyList[i]->X && CEnemy::EnemyList[i]->oldY >= CEnemy::EnemyList[i]->Y){
                    CEnemy::EnemyList[i]->CanJump = true;
                    CEnemy::EnemyList[i]->Jump();
                }
            }
            CEnemy::EnemyList[i]->MoveRight = true;
            CEnemy::EnemyList[i]->MoveLeft = false;

            CEnemy::EnemyList[i]->oldX = CEnemy::EnemyList[i]->X;

            CEnemy::EnemyList[i]->Anim_Control.Oscillate = true;
        }
        else if((CEnemy::EnemyList[i]->X - Player.X < 500) && CEnemy::EnemyList[i]->X > Player.X) {
            if(CEnemy::EnemyList[i]->MoveLeft)
            {
                if(CEnemy::EnemyList[i]->oldX == CEnemy::EnemyList[i]->X && CEnemy::EnemyList[i]->oldY >= CEnemy::EnemyList[i]->Y){
                    CEnemy::EnemyList[i]->CanJump = true;
                    CEnemy::EnemyList[i]->Jump();
                }
            }
            CEnemy::EnemyList[i]->MoveLeft = true;
            CEnemy::EnemyList[i]->MoveRight = false;

            CEnemy::EnemyList[i]->oldX = CEnemy::EnemyList[i]->X;
            CEnemy::EnemyList[i]->oldY = CEnemy::EnemyList[i]->Y;

            CEnemy::EnemyList[i]->Anim_Control.Oscillate = true;


        }
        if((Player.X - CEnemy::EnemyList[i]->X) > 250 || (CEnemy::EnemyList[i]->X - Player.X) > 250)
        {
            CEnemy::EnemyList[i]->MoveLeft = false;
            CEnemy::EnemyList[i]->MoveRight = false;
            CEnemy::EnemyList[i]->Anim_Control.Oscillate = false;

        }
    }

    //Collision Events
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

        if(EntityA == NULL || EntityB == NULL) continue;

        if(EntityA->OnCollision(EntityB)) {
            EntityB->OnCollision(EntityA);
            if((Player.Y + Player.Height) > (CEnemy::EnemyList[i]->Y + CEnemy::EnemyList[i]->Height))
            {
                Reset();
            }

        }
    }
    CEntityCol::EntityColList.clear();
}

void CAppStateGame::OnRender(SDL_Surface* Surf_Display) {
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);

	CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnRender(Surf_Display);
    }
}

CAppStateGame* CAppStateGame::GetInstance() {
    return &Instance;
}


void CAppStateGame::Reset()
{
            Player.IsJumping = false;
            Player.MoveLeft = false;
            Player.MoveRight = false;
            Player.X = 0;
            Player.Y = 0;
}
