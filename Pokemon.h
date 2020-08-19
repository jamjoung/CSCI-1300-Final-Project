#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
using namespace std;


class Pokemon //general pokemon class for user, trainer, wild
{
    public: 
    Pokemon(); 
    Pokemon(string stats[9]);
    
    
    int damageDone(Pokemon user_pokemon[], Pokemon trainer_pokemon[]); //user == attacker, trainer == enemy. in a battle, compares the attack and defense of attacking pokemon and enemy and calculates the damage that is dealt to the enemy
    int levelUp(string pokemon_name); //when pokemon wins battle, level up and returns new level (leveling up means increase in stats, health, attack, etc)
    void setPokedex();//(array of non-active pkmn)
    void setPokemonLocation(int row, int column);
    int getPokemonLocation();
    string viewPokedex();
    
    void setNumber(int number);
    int getNumber();
    void setName(string pokemon_name);
    string getName();
    void setAttack(int attack);
    int getAttack();
    void setDefense(int defense);
    int getDefense();
    void setMaxHealth(int health);
    int getMaxHealth();
    void setSpeed(int speed);
    int getSpeed();
    void setMax(int max);
    int getMax();
    void setType1(string type1);
    string getType1();
    void setType2(string type2);
    string getType2();
    void setCurrentHealth(int current_health);
    int getCurrentHealth();
    
    
    void setLocationRow(int row);
    int getLocationRow();
    void setLocationCol(int column);
    int getLocationCol();
   
    void getStats();
   //void levelUp();
   
    private:
    string pokemon_name;
    string pokemon_file;
    int pokemon_level;
    int number;
    int attack;
    int defense;
    int max_health;
    int current_health;
    int speed;
    int max;
    int row;
    int column;
    string type1;
    string type2;
    
    
    
};

#endif