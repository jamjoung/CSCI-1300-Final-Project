#include <iostream> 
#include <string> 
#include <vector>
#include "Player.h"
#include "Trainer.h"
#include "split.cpp"
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map
{
    public:
        
        Map();
        void generateWild(string pokemon_file); //creates 20 wild pokemon randomly scattered
        void readMap(string map_file);
        void displayMap(Player *playerPointer); //shows 7x7 area around you
        void initializeWild(vector<Pokemon> all_pokemon);
        void assignWild();
        void initializeTrainers(vector<Pokemon> all_pokemon, vector<Trainer> *trainers);
        bool travel(Player *playerPointer, char direction);
        void moveWild();
        int findWildPKMN(Player *playerPointer); //finds pokemon around player that can be caught
        Pokemon getWildPokemon(int index);
        void setWildBool(bool wild_encounter);
        bool getWildBool();
        void statsWild(int index);
        
        void swapPokemon(); //switches pokemon from pokedex at cente4
        void healPokemon(); //heals party if user is at center
        void teleportWild(int index); //if trainer is defeated, teleport to nearest center
        void teleportTrainer();
        void takeDamageWild(int index, int damage);
        void deleteWild(int index);
    //gym and center
        bool checkGymLocation(Player player);
        bool checkCenterLocation(Player player);
        void centerMenu(Player *playerPoint);
        void battleGym(); //enters battle only if there is a trainer at the gym (cannot flee)
    
    
        void tryLuck(Player *playerPointer);
        
    private:
        
        string pokemon_file;
        string map_file;
        string choice;
        int selection;
        string map_array[25][16];
        vector<Pokemon> wild_pokemon;
        int index;
        bool wild_encounter = false;
        
        int rows;
        int columns;
};

#endif