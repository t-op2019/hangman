//
//  main.cpp
//  hangman
//
//  Created by Dư Võ on 3/31/22.
//

#include <iostream>
#include "utils/SDL_Utils.h"
#include <fstream>

int main(int argc, const char * argv[]) {
    const string defaultFilePath = "assets/data/";
    string content;
    ifstream file(defaultFilePath + "hangman_dictionary.txt");
    if (file) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
    file.close();
    std::cout << "Hello, World!\n";
    return 0;
}
