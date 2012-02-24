#ifndef Weapon_H_INCLUDED
#define Weapon_H_INCLUDED

#include "Item.h"

class Weapon : public Item
{
public:

    int damage;
    int range;
    int speed;
    bool canHit;

    int onHitTime;
    int hitTimer;

    Weapon();
    ~Weapon();

    // bool OnLoad(char* File, int Width, int Height, int MaxFrames);

    bool OnLoad(char* File, int Width, int Height);

    void OnLoop(float playerX, float playerY);

    void OnRender(SDL_Surface* Surf_Display);

    void OnCleanup();

    void OnAnimate();

    bool OnCollision(CEntity* Entity);

    void DoDamage();
};

#endif // Weapon_H_INCLUDED
