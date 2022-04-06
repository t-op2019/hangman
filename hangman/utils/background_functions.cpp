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

SDL_Texture *background, *playButton, *replayButton, *stages[9];

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
    
    for (int i = 0; i < 9; i++) {
        stages[i] = loadTexture(defaultRoutes + "hangman" + to_string(i) + ".png", renderer);
        if (stages[i] == NULL) {
            stagesLoaded = false;
            break;
        }
    }
    
    if (background == NULL | stagesLoaded == false) {
        unloadAllTexture();
        exit(1);
    }
    rerender("play");
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

void rerender(const string gameState) {
    SDL_RenderClear(renderer);
    // render background
    renderTexture(background, renderer, 0, 0, width, height);
    if (gameState == "play") {
        renderPlayButton();
        renderText(48, "HANGMAN", renderer, width / 3, 100);
    }
    renderPresent();
}

void renderPlayButton() {
    renderTexture(playButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}

SDL_Rect playButtonRect() {
    return renderButton(playButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}

SDL_Rect replayButtonRect() {
    return renderButton(replayButton, renderer, width / 2 - 90, height / 4 * 3, 180, 64);
}
