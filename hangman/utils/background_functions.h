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
#include <vector>
using namespace std;

void loadAllTexture();

void unloadAllTexture();

void renderPresent();

void rerender(const string gameState, int stage, int wordLength, vector<int> indexes, vector<string> letters);

void renderPlayButton();

void renderReplayButton();

SDL_Rect playButtonRect();

SDL_Rect replayButtonRect();

void renderStage(int stage);

void renderLetterSlots(int x);

void renderGuessedWords(vector<int> indexes, vector<string> letters);

#endif /* background_functions_h */
