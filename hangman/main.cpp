//
//  main.cpp
//  hangman
//
//  Created by Dư Võ on 3/31/22.
//

#include <iostream>
#include "utils/SDL_Utils.h"
#include "utils/background_functions.h"
#include <fstream>
#include <cstdlib>

int randomIndex(int length);

int main(int argc, const char * argv[]) {
    const string defaultFilePath = "assets/data/";
    string content;
    int num_of_lines = 0;
    ifstream file(defaultFilePath + "hangman_dictionary.txt");
    
    // count the number of lines in the dictionary file
    while (getline(file, content)) {
            ++num_of_lines;
    }
    
    int index = randomIndex(num_of_lines);
    
    // indicates if the game is running
    bool isRunning = true;
    // the state of the game
    string gameState = "play";
    
    SDL_Event event;
    
    SDL_Point mousePosition;
    
    SDL_Rect playRect = playButtonRect();
    SDL_Rect replayRect = replayButtonRect();
    
    loadAllTexture();
    while (isRunning) {
        if ( SDL_WaitEvent(&event) == 0) continue;
        
        if (event.type == SDL_QUIT) {
            isRunning = false;
            unloadAllTexture();
            exit(1);
        }
        
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mousePosition.x = event.button.x;
            mousePosition.y = event.button.y;
            if (gameState == "play") {
                if (SDL_PointInRect(&mousePosition, &playRect)) {
                    cout << "Clicked on play" << endl;
                }
            } else if (gameState == "replay") {
                if (SDL_PointInRect(&mousePosition, &replayRect)) {
                    cout << "Clicked on replay" << endl;
                }
            }
        }
        
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                isRunning = false;
//                unloadAllTexture();
//                exit(1);
//            }
//        }
    }
    
    file.close();
    return 0;
}

int randomIndex(int length) {
    return rand() % length;
}
