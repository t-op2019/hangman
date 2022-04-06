//
//  background_functions.h
//  hangman
//
//  Created by Dư Võ on 4/6/22.
//

#ifndef background_functions_h
#define background_functions_h

#include "SDL_Utils.h"
#include <iostream>
using namespace std;

void loadAllTexture();

void unloadAllTexture();

void renderPresent();

void rerender(const string gameState);

void renderPlayButton();

SDL_Rect playButtonRect();

SDL_Rect replayButtonRect();

#endif /* background_functions_h */
