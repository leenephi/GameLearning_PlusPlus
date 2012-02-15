#ifndef SHORTRANGE_H_INCLUDED
#define SHORTRANGE_H_INCLUDED

#include "CEntity.h"

class ShortRange : public CEntity
{
public:

    int damage;
    int range;
    int speed;

    ShortRange();

    bool OnLoad(char* File, int Width, int Height, int MaxFrames);

    void OnLoop();

    void OnRender(SDL_Surface* Surf_Display);

    void OnCleanup();

    void OnAnimate();

    bool OnCollision(CEntity* Entity);
};

#endif // SHORTRANGE_H_INCLUDED
