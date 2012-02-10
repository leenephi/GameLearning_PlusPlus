#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "CEntity.h"

class CEnemy : public CEntity {
    public:

        static std::vector<CEnemy*>    EnemyList;

        CEnemy(float x, float y);

		bool OnLoad(char* File, int Width, int Height, int MaxFrames);

        void OnLoop();

        void OnRender(SDL_Surface* Surf_Display);

        void OnCleanup();

        void OnAnimate();

        bool OnCollision(CEntity* Entity);

        void AddEnemy(float x, float y);
};

#endif // CENEMY_H_INCLUDED
