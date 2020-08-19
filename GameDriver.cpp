
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "Game.cpp"


using namespace std;

int main()
{
    Game game("mapPoke.txt");
    game.readPokemon("Pokemon.txt");
    game.initializeWild();
    game.assignWild();


    
    game.introduction();
    game.displayMap();
    cout << endl;
    
    
    game.initializeTrainers();
    game.findWild();
    game.choiceMenu();
    //game.rest();

}
    
    
