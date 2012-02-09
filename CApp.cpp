//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;

    Running = true;
}

//------------------------------------------------------------------------------
int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

void CApp::Reset()
{
            Player.IsJumping = false;
            Player.MoveLeft = false;
            Player.MoveRight = false;
            Enemy.MoveLeft = false;
            Enemy.MoveRight = false;
            Player.X = 0;
            Player.Y = 0;
            Enemy.X = 500;
            Enemy.Y = 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
