//=============================================================================
#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CEntity.h"
#include "Weapon.h"

//=============================================================================
class CPlayer : public CEntity
{
public:
    CPlayer();

    ~CPlayer();

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

    void Attack();

    void TakeDamage(int damage);

    void Wield(CEntity* itemToWield);
};

//=============================================================================

#endif


