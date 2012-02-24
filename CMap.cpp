//=============================================================================
#include "CMap.h"
#include "CEnemy.h"
#include <time.h>

//=============================================================================
CMap::CMap()
{
    Surf_Tileset_Passables = NULL;
    Surf_Tileset_Impassables = NULL;
}

//=============================================================================
bool CMap::OnLoad(char* File, int MapX, int MapY)
{

    TileList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            CTile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            if(tempTile.TileID == 0)
            {
                // set a random tile for the grass/flowers
                srand(X * Y);
                int newID = rand() % 4;
                tempTile.TileID = newID;
            }

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }



    AddEnemies(MapX, MapY);
    fclose(FileHandle);
    return true;
}

void CMap::AddEnemies(int MapX, int MapY)
{

    int ID = 0;

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            if(TileList[ID].TypeID != TILE_TYPE_ENEMY1)
            {
                ID++;
                continue;
            }

            TileList[ID].TypeID = TILE_TYPE_PASSABLE;

            float enemyX = MapX + (X * TILE_SIZE);
            float enemyY = MapY + (Y * TILE_SIZE) - 20;

            CEnemy* newenemy = new CEnemy(enemyX, enemyY, "enemy.png", 34, 47, 3);

            newenemy->Type = ENTITY_TYPE_ENEMY;

            CEntity::EntityList.push_back(newenemy);

            ID++;

        }

    }

}

//-----------------------------------------------------------------------------
void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY)
{
    if(Surf_Tileset_Passables == NULL || Surf_Tileset_Impassables == NULL) return;

    int TilesetWidth;
    int TilesetHeight;

    int ID = 0;

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            if(TileList[ID].TypeID == TILE_TYPE_NONE)
            {
                ID++;
                continue;
            }

            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);

            if(TileList[ID].TypeID == TILE_TYPE_PASSABLE)
            {
                TilesetWidth  = Surf_Tileset_Passables->w / TILE_SIZE;
                //TilesetHeight = Surf_Tileset_Passables->h / TILE_SIZE;

                int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
                int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

                CSurface::OnDraw(Surf_Display, Surf_Tileset_Passables, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            }

            else if(TileList[ID].TypeID == TILE_TYPE_IMPASSABLE)
            {
                TilesetWidth  = Surf_Tileset_Impassables->w / TILE_SIZE;
                //TilesetHeight = Surf_Tileset_Impassables->h / TILE_SIZE;

                int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
                int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

                CSurface::OnDraw(Surf_Display, Surf_Tileset_Impassables, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            }
            ID++;
        }
    }
}

//=============================================================================
CTile* CMap::GetTile(int X, int Y)
{
    int ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size())
    {
        return NULL;
    }

    return &TileList[ID];
}

//=============================================================================
