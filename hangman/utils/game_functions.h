//
//  game_functions.h
//  hangman
//
//  Created by Dư Võ on 4/7/22.
//

#ifndef game_functions_h
#define game_functions_h

#include "background_functions.h"

void playGame(const string constWord, string &word, int &stage, vector<int> &indexes, vector<string> &letters);

string getInput();

int evaluateAnswer(string letter, string word);

#endif /* game_functions_h */
