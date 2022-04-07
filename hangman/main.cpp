//
//  main.cpp
//  hangman
//
//  Created by Dư Võ on 3/31/22.
//

#include <iostream>
#include "utils/SDL_Utils.h"
#include "utils/background_functions.h"
#include "utils/game_functions.h"
#include <fstream>
#include <cstdlib>

int randomIndex(int length);

int getLengthOfFile();

string getWord(int index);

int main(int argc, const char * argv[]) {
    const string defaultFilePath = "assets/data/";
    string content;
    int numOfLines = getLengthOfFile();
    ifstream file(defaultFilePath + "hangman_dictionary.txt");
    
//    int index = randomIndex(numOfLines);
    
    // indicates if the game is running
    bool isRunning = true;
    // the state of the game
    string gameState = "play";
    
    SDL_Event event;
    
    SDL_Point mousePosition;
    
    SDL_Rect playRect = playButtonRect();
    SDL_Rect replayRect = replayButtonRect();
    
    vector<int> indexes;
    vector<string> letters;
    
    string randomizedWord;
    int stage = 8;
    
    string tempWord;
    
    loadAllTexture();
    while (isRunning) {
        if ( SDL_WaitEvent(&event) == 0) continue;
        
        if (event.type == SDL_QUIT) {
            isRunning = false;
            unloadAllTexture();
            exit(1);
        }
        
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // get mouse position when mouse is clicked
            mousePosition.x = event.button.x;
            mousePosition.y = event.button.y;
            if (gameState == "play") {
                if (SDL_PointInRect(&mousePosition, &playRect)) {
                    int index = randomIndex(numOfLines);
                    randomizedWord = getWord(index);
                    tempWord = randomizedWord;
                    gameState = "playing";
                }
            } else if (gameState == "replay" | gameState == "lose") {
                if (SDL_PointInRect(&mousePosition, &replayRect)) {
                    indexes = {};
                    letters = {};
                    stage = 8;
                    int index = randomIndex(numOfLines);
                    randomizedWord = getWord(index);
                    tempWord = randomizedWord;
                    gameState = "playing";
                }
            }
        }
        
        if (gameState == "playing") {
            playGame(randomizedWord, tempWord, stage, indexes, letters);
            if (letters.size() == randomizedWord.length()) {
                gameState = "replay";
            }
            
            if (stage == 0) {
                gameState = "lose";a
            }
        }
        
        if (gameState == "replay" | gameState == "lose") {
            rerender(gameState, stage, randomizedWord.length(), indexes, letters);
        }
    }
    
    file.close();
    return 0;
}

int randomIndex(int length) {
    return rand() % length;
}

int getLengthOfFile() {
    const string defaultPath = "assets/data/";
    int numOfLines = 0;
    string content;
    ifstream file(defaultPath + "hangman_dictionary.txt");
    while (getline(file, content)) {
        ++numOfLines;
    }
    
    return numOfLines;
}

string getWord(int index) {
    const string defaultPath = "assets/data/";
    int numOfLines = 0;
    string content;
    ifstream file(defaultPath + "hangman_dictionary.txt");
    while (getline(file, content)) {
        if (numOfLines == index) {
            return content;
        }
        numOfLines++;
    }
    return "";
}
