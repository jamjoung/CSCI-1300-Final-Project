#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Pokemon.h"
#include "Pokemon.cpp"
#include "Map.h"
#include "Map.cpp"

#include "Player.cpp"
#include "Trainer.cpp"

using namespace std;

#ifndef GAME_H
#define GAME_H


class Game
{
    public: 
    //introduction
    Game();
    Game(string map_file);
    void introduction();
    void choiceMenu();
    void readPokemon(string pokemon_file);
    void initializeWild();
    void assignWild();
    void moveWild();
    void setName(string player_name);
    string getName();
    void setPokemon();
    void displayMap();
    void travel(char direction);
    
    
    //trainers
    void initializeTrainers();
    void findWild();
    void gymMenu(Player player);
    void battleWild(int index);
    void battleGym();
    
    //choice on map (in a while loop?)
    string rest(); //heals pokemon
    void quit();
    
    //battle
   
    string switch_active(int pokemon_number);
    void flee(); //only for wild pokemon, compare speeds
    
    //random events
    void second_wild(); //30% chance another one appears after initial encounter
    void hidden_treasure(); //25% chance of finding (50/50 for pokeball or poffin)
    void death(); //20% chance of one pokemon dying
    
    
    private:
    string map_file;
    Player player;
    Map map;
    vector<Trainer> trainers;
    vector<Pokemon> all_pokemon;
    string username;
    int column;
    int row;
    char direction;
    int encounters;
    
    int pokemon_number;
    
    string pokemon_file;
    
};

#endif