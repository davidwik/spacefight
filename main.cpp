#include "game.h"
#include "utils.h"
#include <iostream>
#include <SDL/SDL.h>
int main (int argc, char* argv[]){
    try {
        printf("Working dir is: %s\n", getDirectory().c_str());
    } catch(int e){
        ;
    }
/*
    string d << std::dec << (int) getFileContents("dog");
    string score = 0;
    if(d != ""){
        score = d;
    }
    std::cout << "SCORE: " << score;
    string s << std::hex << 400;
    writeToFile("300", "dog");
*/
    Game g;
    g.runState(Game::States::MENU);

    return 0;

}
