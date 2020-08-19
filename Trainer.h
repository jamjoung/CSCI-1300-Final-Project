#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef TRAINER_H
#define TRAINER_H

class Trainer
{
    public:
    Trainer();
    Trainer(string name, int trainer_row, int trainer_column);
    void addPKMN(Pokemon pokemon);
    void setTrainerName(string name);
    string getTrainerName();
    void setTrainerRow(int rows);
    int getTrainerRow();
    void setTrainerCol(int columns);
    int getTrainerCol();
    void transferPokemon(); //after defeated, 
    
    private:
    int trainer_row;
    int trainer_column;
    string trainer_name;
    vector<Pokemon> trainer_pokemon;
    vector<Pokemon> all_pokemon;
    
};
   
   #endif