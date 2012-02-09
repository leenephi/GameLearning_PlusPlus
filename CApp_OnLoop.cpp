//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnLoop() {
    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();
    }

    Enemy.CanJump = false;

    if((Player.X - Enemy.X < 250) && Enemy.X < Player.X) {
        if(Enemy.MoveRight)
        {
            if(Enemy.oldX == Enemy.X){
                Enemy.CanJump = true;
                Enemy.Jump();
            }
        }
        Enemy.MoveRight = true;
        Enemy.MoveLeft = false;
        Enemy.oldX = Enemy.X;
    }
    else if((Enemy.X - Player.X < 250) && Enemy.X > Player.X) {
        if(Enemy.MoveLeft)
        {
            if(Enemy.oldX == Enemy.X){
                Enemy.CanJump = true;
                Enemy.Jump();
            }
        }
        Enemy.MoveLeft = true;
        Enemy.MoveRight = false;
        Enemy.oldX = Enemy.X;
    }
    if((Player.X - Enemy.X) > 250 || (Enemy.X - Player.X) > 250)
    {
        Enemy.MoveLeft = false;
        Enemy.MoveRight = false;
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

    CFPS::FPSControl.OnLoop();

    char Buffer[255];
    sprintf(Buffer, "FPS: %d", CFPS::FPSControl.GetFPS());
    SDL_WM_SetCaption(Buffer, Buffer);
}

//==============================================================================
