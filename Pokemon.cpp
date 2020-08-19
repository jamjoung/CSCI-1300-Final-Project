#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;

Pokemon :: Pokemon()
{
    pokemon_name = "";
    attack = 0;
    defense = 0;
    max_health = 0;
    current_health = 0;
    speed = 0;
    max = 0; 
    type1 = "";
    type2 = "";
    
}

Pokemon :: Pokemon(string stats[9])
{
    number = stoi(stats[0]);
    pokemon_name = stats[1];
    max_health = stoi(stats[2]);
    current_health = max_health;
    attack = stoi(stats[3]);
    defense = stoi(stats[4]);
    speed = stoi(stats[5]);
    max = stoi(stats[6]);
    type1 = stats[7];
    type2 = stats[8];
    
}
void Pokemon :: setNumber(int number_id)
{
    number = number_id;
}
int Pokemon :: getNumber()
{
    return number;
}
void Pokemon :: setName(string pkmn_name)
{
    pokemon_name = pkmn_name;
}
string Pokemon :: getName()
{
    return pokemon_name;
}
void Pokemon :: setAttack(int attack_value)
{
    attack = attack_value;
}
int Pokemon :: getAttack()
{
    return attack;
}
void Pokemon :: setDefense(int defense_value)
{
    defense = defense_value;
}
int Pokemon :: getDefense()
{
    return defense;
}
void Pokemon :: setMaxHealth(int healthpoints)
{
    max_health = healthpoints;
}
int Pokemon :: getMaxHealth()
{
    return max_health;
}
void Pokemon :: setSpeed(int speed_value)
{
    speed = speed_value;
}
int Pokemon :: getSpeed()
{
    return speed;
}
void Pokemon :: setMax(int max_value)
{
    max = max_value;
}
int Pokemon :: getMax()
{
    return max;
}
void Pokemon:: setType1(string type_name)
{
    type1 = type_name;
}
string Pokemon :: getType1()
{
    return type1;
}
void Pokemon :: setType2(string type_name)
{
    type2 = type_name;
}
string Pokemon :: getType2()
{
    return type2;
}
   
void Pokemon :: setCurrentHealth(int current)
{
    current_health = current;
    if (current < 0) 
    {
        current_health = 0;
    }
}

int Pokemon :: getCurrentHealth()
{
    return current_health;
}

void Pokemon :: setLocationRow(int rowc)
{
    row = rowc;
}

int Pokemon :: getLocationRow()
{
    return row;
}

void Pokemon :: setLocationCol(int columnc)
{
    column = columnc;
}

int Pokemon :: getLocationCol()
{
    return column;
}


int Pokemon :: damageDone(Pokemon user_pokemon[], Pokemon trainer_pokemon[]) //user == attacker, trainer == enemy
    {
        //in a battle, compares the attack and defense of attacking pokemon and enemy and calculates the damage that is dealt to the enemy
    }
    

void Pokemon :: setPokedex() //when you catch pokemon while having 6 active in your party 
{
    //if active == 6, pokemon added to array of pokemon objects of pokedex
    //if there are already pokemon in pokedex, adds onto the array
    //Pokemon pokedex[];
}

string Pokemon :: viewPokedex()
{
    //return pokedex[];
}

void Pokemon :: getStats()
{
    cout << "Name: " << pokemon_name;
    cout << ", HP: " << current_health;
    cout << ", A: " << attack;
    cout << ", D: " << defense;
    cout << ", S: " << speed;
    cout << ", M: " << max;
    cout << endl;
}