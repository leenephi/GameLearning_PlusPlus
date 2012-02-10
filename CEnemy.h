#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CEntity.h"

class CEnemy : public CEntity {
    public:

        static std::vector<CEnemy*>    EnemyList;

        CEnemy(int startX, int startY);

		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);
};

#endif // CENEMY_H_INCLUDED
