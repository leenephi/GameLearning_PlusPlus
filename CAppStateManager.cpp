#include "CAppStateManager.h"

// Refer to your Other App States Here
#include "CAppStateIntro.h"
#include "CAppStateGame.h"

CAppState* CAppStateManager::ActiveAppState = 0;

void CAppStateManager::OnEvent(SDL_Event* EventHolder) {
    if(ActiveAppState) ActiveAppState->OnEvent(EventHolder);
}

void CAppStateManager::OnLoop() {
    if(ActiveAppState) ActiveAppState->OnLoop();
}

void CAppStateManager::OnRender(SDL_Surface* Surf_Display) {
    if(ActiveAppState) ActiveAppState->OnRender(Surf_Display);
}

void CAppStateManager::SetActiveAppState(int AppStateID) {
    if(ActiveAppState) ActiveAppState->OnDeactivate();

    // Also, add your App State Here so that the Manager can switch to it
    switch(AppStateID){
        case APPSTATE_NONE:{
            ActiveAppState = 0;
            break;
        }
        case APPSTATE_INTRO:{
            ActiveAppState = CAppStateIntro::GetInstance();
            break;
        }
        case APPSTATE_GAME:{
            ActiveAppState = CAppStateGame::GetInstance();
            break;
        }
        default:{
        }
    }

    if(ActiveAppState) ActiveAppState->OnActivate();
}

CAppState* CAppStateManager::GetActiveAppState() {
    return ActiveAppState;
}
