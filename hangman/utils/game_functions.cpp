//
//  game_functions.cpp
//  hangman
//
//  Created by Dư Võ on 4/7/22.
//

#include "game_functions.h"

void playGame(const string constWord, string &word, int &stage, vector<int> &indexes, vector<string> &letters) {
    rerender("playing", stage, constWord.length(), indexes, letters);
    cout << word << endl;
    string playerGuess = getInput();
    if (evaluateAnswer(playerGuess, word) == -1) {
        stage--;
    } else {
        int answerIndex = evaluateAnswer(playerGuess, word);
        char guess[2];
        strcpy(guess, playerGuess.c_str());
        indexes.push_back(answerIndex);
        letters.push_back(playerGuess);
        word[answerIndex] = '@';
    }
}

string getInput() {
    SDL_Event event;
    bool isListening = true;
    while (SDL_PollEvent(&event) | isListening) {
        if (event.type == SDL_QUIT) {
            isListening = false;
            unloadAllTexture();
            exit(1);
        }

        if (event.type == SDL_KEYDOWN) {
            string res = interpretKey(&event.key);
            isListening = false;
            return res;
        }
    }
    return "";
}

int evaluateAnswer(string letter, string word) {
    for (int i = 0; i < word.length(); i++) {
        if (string(1, toupper(word[i])) == letter) {
            return i;
        }
    }
    return -1;
}
