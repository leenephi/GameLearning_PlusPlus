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

    CFPS::FPSControl.OnLoop();

    char Buffer[255];
    sprintf(Buffer, "FPS: %d", CFPS::FPSControl.GetFPS());
    SDL_WM_SetCaption(Buffer, Buffer);
}

//==============================================================================
