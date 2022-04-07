//
//  background_functions.cpp
//  hangman
//
//  Created by Dư Võ on 4/6/22.
//

#include "background_functions.h"
#include "SDL_Utils.h"

// global variables
const string windowTitle = "Hangman";
SDL_Window* window;
SDL_Renderer* renderer;

SDL_Texture *background, *playButton, *replayButton, *letterSlot, *stages[9];

int width = 800, height = 600;

// basic background functions (load/unload textures, render and rerender screen
// *********************************************************************************

void loadAllTexture() {
    initSDL(window, renderer, windowTitle, width, height);
    const string defaultRoutes = "assets/images/";
    bool stagesLoaded = true;
    
    background = loadTexture(defaultRoutes + "background.png", renderer);
    playButton = loadTexture(defaultRoutes + "play_game.png", renderer);
    replayButton = loadTexture(defaultRoutes + "replay.png", renderer);
    letterSlot = loadTexture(defaultRoutes + "letter_slot.png", renderer);
    
    for (int i = 0; i < 9; i++) {
        stages[i] = loadTexture(defaultRoutes + "hangman" + to_string(i) + ".png", renderer);
        if (stages[i] == NULL) {
            stagesLoaded = false;
            break;
        }
    }
    
    if (background == NULL | stagesLoaded == false | playButton == NULL | replayButton == NULL | letterSlot == NULL) {
        unloadAllTexture();
        exit(1);
    }
    rerender("play", 8, 0, {}, {});
}

void unloadAllTexture() {
    SDL_DestroyTexture(background);
    
    for (int i = 0; i < 9; i++) {
        SDL_DestroyTexture(stages[i]);
    }
    
    quitSDL(window, renderer);
}

void renderPresent() {
    SDL_RenderPresent(renderer);
}

// gameState: the current state of the game:
// 1. play: when the application is started -> start at the main menu screen -> display the play button (and the title of the game)
// 2. playing: the game is started -> display the hangman's stages, letter slots and the letters that the player has guessed correctly
// 3. replay: when the player has won (or is defeated) -> maintain the state of the game in "playing" state and render the "play again" button

void rerender(const string gameState, int stage, int wordLength, vector<int> indexes, vector<string> letters) {
    SDL_RenderClear(renderer);
    // render background
    renderTexture(background, renderer, 0, 0, width, height);
    if (gameState == "play") {
        renderPlayButton();
        renderText(48, "HANGMAN", renderer, width / 3, 100);
    } else {
        renderStage(stage);
        for (int i = 0; i < wordLength; i++) {
            renderLetterSlots(100 + 40 * i);
        }
        renderGuessedWords(indexes, letters);
        if (gameState == "replay" | gameState == "lose") {
            renderReplayButton();
            if (gameState == "replay") {
                renderText(36, "You have won", renderer, width / 3, 100);
            } else {
                renderText(36, "You have lost", renderer, width / 3, 100);
            }
        }
    }
    renderPresent();
}

// render clickable play and replay button
// ****************************************************************************************
void renderPlayButton() {
    renderTexture(playButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}

void renderReplayButton() {
    renderTexture(replayButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}

SDL_Rect playButtonRect() {
    return renderButton(playButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}

SDL_Rect replayButtonRect() {
    return renderButton(replayButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}
// ****************************************************************************************

// render hangman stages
void renderStage(int stage) {
    renderTexture(stages[stage], renderer, width - 250, 0, 250, 320);
}

void renderLetterSlots(int x) {
    renderTexture(letterSlot, renderer, x, 360, 30, 10);
}

void renderGuessedWords(vector<int> indexes, vector<string> letters) {
    for (int i = 0; i < letters.size(); i++) {
        char guess[2];
        strcpy(guess, letters[i].c_str());
        renderText(24, guess, renderer, 100 + 40 * indexes[i], 300);
    }
}
