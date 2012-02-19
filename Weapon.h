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

    Weapon();

    // bool OnLoad(char* File, int Width, int Height, int MaxFrames);

    bool OnLoad(int Width, int Height);

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

    void OnCleanup();

    void OnAnimate();

    bool OnCollision(CEntity* Entity);

    void DoDamage(float playerX, float playerY, int playerW, int playerH);
};

#endif // Weapon_H_INCLUDED
