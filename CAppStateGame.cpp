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



    Enemy.OnLoad("enemy.png", 34, 47, 3);


    CEntity::EntityList.push_back(&Player);
    CEntity::EntityList.push_back(&Enemy);

    Enemy.X = 500;

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
    Enemy.CanJump = false;

    if((Player.X - Enemy.X < 250) && Enemy.X < Player.X) {
        if(Enemy.MoveRight)
        {
            if(Enemy.oldX == Enemy.X && Enemy.oldY >= Enemy.Y){
                Enemy.CanJump = true;
                Enemy.Jump();
            }
        }
        Enemy.MoveRight = true;
        Enemy.MoveLeft = false;

        Enemy.oldX = Enemy.X;

        Enemy.Anim_Control.Oscillate = true;

//
    }
    else if((Enemy.X - Player.X < 250) && Enemy.X > Player.X) {
        if(Enemy.MoveLeft)
        {
            if(Enemy.oldX == Enemy.X && Enemy.oldY >= Enemy.Y){
                Enemy.CanJump = true;
                Enemy.Jump();
            }
        }
        Enemy.MoveLeft = true;
        Enemy.MoveRight = false;

        Enemy.oldX = Enemy.X;
        Enemy.oldY = Enemy.Y;

        Enemy.Anim_Control.Oscillate = true;


    }
    if((Player.X - Enemy.X) > 250 || (Enemy.X - Player.X) > 250)
    {
        Enemy.MoveLeft = false;
        Enemy.MoveRight = false;
        Enemy.Anim_Control.Oscillate = false;

    }

    //Collision Events
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
        CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
        CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;

        if(EntityA == NULL || EntityB == NULL) continue;

        if(EntityA->OnCollision(EntityB)) {
            EntityB->OnCollision(EntityA);
            if((Player.Y + Player.Height) > (Enemy.Y + Enemy.Height))
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
            Enemy.MoveLeft = false;
            Enemy.MoveRight = false;
            Player.X = 0;
            Player.Y = 0;
            Enemy.X = 500;
            Enemy.Y = 0;
}
