#include <iostream>
#include <vector>
#include <string>

using namespace std;


Trainer :: Trainer()
{
   trainer_row = 0;
   trainer_column = 0;
   trainer_name = "";
}
Trainer :: Trainer (string name, int row, int column)
{
    trainer_name = name;
    trainer_row = row;
    trainer_column = column;
}
void Trainer :: setTrainerName(string name)
{
    trainer_name = name;
}

string Trainer :: getTrainerName()
{
    return trainer_name;
}

void Trainer :: setTrainerRow(int rows)
{
    trainer_row = rows;
}
int Trainer :: getTrainerRow()
{
    return trainer_row;
}
void Trainer :: setTrainerCol(int columns)
{
    trainer_column = columns;
}
int Trainer :: getTrainerCol()
{
    return trainer_column;
}

void Trainer :: addPKMN(Pokemon pokemon)
{
    trainer_pokemon.push_back(pokemon);
}

    


/*void Trainer :: transferPokemon() //after defeated, 
{
    //after defeated, transfer pokemon from their array to user's.
}
    */
    
 