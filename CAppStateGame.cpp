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

void CAppStateGame::OnActivate() {
    CArea::AreaControl.OnLoad("./maps/level1.area");

    Player.OnLoad("player.png", 33, 56, 13);
    Player.Type = ENTITY_TYPE_PLAYER;

    CEntity::EntityList.push_back(&Player);

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
    for(int i = 0; i < CEntity::EntityList.size(); i++) {
        // continue with next entity if this one is not an enemy.. for example, a player, who then wouldn't be able to jump
        if(CEntity::EntityList[i]->Type != ENTITY_TYPE_ENEMY) continue;
        CEntity::EntityList[i]->CanJump = false;
        if((Player.X - CEntity::EntityList[i]->X < 500) && CEntity::EntityList[i]->X < Player.X) {
            if(CEntity::EntityList[i]->MoveRight)
            {
                if(CEntity::EntityList[i]->oldX == CEntity::EntityList[i]->X && CEntity::EntityList[i]->oldY >= CEntity::EntityList[i]->Y){
                    CEntity::EntityList[i]->CanJump = true;
                    CEntity::EntityList[i]->Jump();
                }
            }
            CEntity::EntityList[i]->MoveRight = true;
            CEntity::EntityList[i]->MoveLeft = false;

            CEntity::EntityList[i]->oldX = CEntity::EntityList[i]->X;

            CEntity::EntityList[i]->Anim_Control.Oscillate = true;
        }
        else if((CEntity::EntityList[i]->X - Player.X < 500) && CEntity::EntityList[i]->X > Player.X) {
            if(CEntity::EntityList[i]->MoveLeft)
            {
                if(CEntity::EntityList[i]->oldX == CEntity::EntityList[i]->X && CEntity::EntityList[i]->oldY >= CEntity::EntityList[i]->Y){
                    CEntity::EntityList[i]->CanJump = true;
                    CEntity::EntityList[i]->Jump();
                }
            }
            CEntity::EntityList[i]->MoveLeft = true;
            CEntity::EntityList[i]->MoveRight = false;

            CEntity::EntityList[i]->oldX = CEntity::EntityList[i]->X;
            CEntity::EntityList[i]->oldY = CEntity::EntityList[i]->Y;

            CEntity::EntityList[i]->Anim_Control.Oscillate = true;


        }
        if((Player.X - CEntity::EntityList[i]->X) > 250 || (CEntity::EntityList[i]->X - Player.X) > 250)
        {
            CEntity::EntityList[i]->MoveLeft = false;
            CEntity::EntityList[i]->MoveRight = false;
            CEntity::EntityList[i]->Anim_Control.Oscillate = false;

        }
    }

    //Collision Events
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

        if(EntityA == NULL || EntityB == NULL) continue;

        if(EntityA->OnCollision(EntityB)) {
            EntityB->OnCollision(EntityA);
            /*if((Player.Y + Player.Height) > (CEntity::EntityList[i]->Y))
            {
                Reset();
            }*/

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

void CAppStateGame::AddEnemy(float x, float y, char* File, int Width, int Height, int MaxFrames) {

    CEnemy* newenemy = new CEnemy(x, y, File, Width, Height, MaxFrames);

    newenemy->Type = ENTITY_TYPE_ENEMY;

    CEntity::EntityList.push_back(newenemy);

}
