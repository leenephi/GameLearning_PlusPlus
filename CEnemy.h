#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CEntity.h"

class CEnemy : public CEntity
{
public:

    CEnemy(float x, float y, char* File, int Width, int Height, int MaxFrames);

    ~CEnemy();

    bool canAttack;

    bool armed;

    int onHitTime;

    int hitTimer;

    CEntity* currentItem;

    bool OnLoad(char* File, int Width, int Height, int MaxFrames);

    void OnLoop(float playerX, float playerY);

    void OnRender(SDL_Surface* Surf_Display);

    void OnCleanup();

    void OnAnimate();

    bool OnCollision(CEntity* Entity);

    void Wield(CEntity* itemToWield);

    void Attack();
};

#endif // CENEMY_H_INCLUDED
