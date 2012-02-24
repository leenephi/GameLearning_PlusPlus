//=============================================================================
#ifndef _CAREA_H_
#define _CAREA_H_

#include "CMap.h"

//=============================================================================
class CArea
{
public:
    static CArea            AreaControl;

public:
    std::vector<CMap>       MapList;

private:
    int                     areaWidth;

    int                     areaHeight;

    int                     MapWidth;
    int                     MapHeight;

    SDL_Surface*			Surf_Tileset_Passables;

    SDL_Surface*            Surf_Tileset_Impassables;

public:
    CArea();

    bool    OnLoad(char* File);

    void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);

    void    OnCleanup();

public:
    CMap*	GetMap(int X, int Y);

    CTile*	GetTile(int X, int Y);
};

//=============================================================================

#endif

