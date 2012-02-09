//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_a: {
			Player.MoveLeft = true;
			break;
		}

		case SDLK_d: {
			Player.MoveRight = true;
			break;
		}

		case SDLK_SPACE: {
		    Player.Jump();
		    Player.IsJumping = true;
		    break;
		}

        case SDLK_ESCAPE: {

            CApp::Reset();
            break;
        }

		default: {
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_a: {
			Player.MoveLeft = false;
			break;
		}

		case SDLK_d: {
			Player.MoveRight = false;
			break;
		}

		default: {
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnExit() {
	Running = false;
}

//==============================================================================
