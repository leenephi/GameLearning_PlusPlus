//=============================================================================
#include "CArea.h"

//=============================================================================
CArea CArea::AreaControl;

//=============================================================================
CArea::CArea()
{
    Surf_Tileset_Passables = NULL;
    Surf_Tileset_Impassables = NULL;

}

//=============================================================================
bool CArea::OnLoad(char* File)
{

    OnCleanup();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    char PassablesFile[255];
    char ImpassablesFile[255];

    fscanf(FileHandle, "%s\n", PassablesFile);
    fscanf(FileHandle, "%s\n", ImpassablesFile);

    if((Surf_Tileset_Passables = CSurface::OnLoad(PassablesFile)) == false)
    {
        return false;
    }
    if((Surf_Tileset_Impassables = CSurface::OnLoad(ImpassablesFile)) == false)
    {
        return false;
    }

    fscanf(FileHandle, "%d:%d\n", &areaWidth, &areaHeight);

    // I added the MapWidth and MapHeight here for the sake of adding enemies in CMap::OnLoad()

    int ID = 0;
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    for(int Y = 0; Y < areaHeight; Y++)
    {
        for(int X = 0; X < areaWidth; X++)
        {
            char MapFile[255];

            fscanf(FileHandle, "%s255 ", MapFile);

            int X = ((ID % areaWidth) * MapWidth);
            int Y = ((ID / areaWidth) * MapHeight);

            CMap tempMap;
            if(tempMap.OnLoad(MapFile, X, Y) == false)
            {
                fclose(FileHandle);

                return false;
            }

            tempMap.Surf_Tileset_Passables = Surf_Tileset_Passables;
            tempMap.Surf_Tileset_Impassables = Surf_Tileset_Impassables;

            MapList.push_back(tempMap);
            ID++;
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

//-----------------------------------------------------------------------------
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY)
{
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * areaWidth);

    for(int i = 0; i < 16; i++)
    {
        int ID = FirstID + ((i / 3) * areaWidth) + (i % 3);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % areaWidth) * MapWidth) + CameraX;
        int Y = ((ID / areaWidth) * MapHeight) + CameraY;

        MapList[ID].OnRender(Surf_Display, X, Y);
    }
}

//-----------------------------------------------------------------------------
void CArea::OnCleanup()
{
    if(Surf_Tileset_Passables)
    {
        SDL_FreeSurface(Surf_Tileset_Passables);
    }
    if(Surf_Tileset_Impassables)
    {
        SDL_FreeSurface(Surf_Tileset_Impassables);
    }

    MapList.clear();
}

//=============================================================================
CMap* CArea::GetMap(int X, int Y)
{
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * areaWidth);

    if(ID < 0 || ID >= MapList.size())
    {
        return NULL;
    }

    return &MapList[ID];
}

//-----------------------------------------------------------------------------
CTile* CArea::GetTile(int X, int Y)
{
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    CMap* Map = GetMap(X, Y);

    if(Map == NULL) return NULL;

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

//=============================================================================
