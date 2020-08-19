#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
    public:
    Player();
    void setName(string username);
    string getName();
    void addPokemon(Pokemon pokemon);
    void viewActivePokemon(); //shows array of 6 pokemon objects
    
    void setPoints(int points);
    int viewPoints();
    int viewStats(); //see total points, total pokemon caught, gym badges
    void setLocationRow(int row1);
    int getLocationRow();
    void setLocationCol(int column1);
    int getLocationCol();
    void setPokeballs(int pokeballs);
    int getPokeballs();
    void setBadges(int badges);
    int getBadges();
    void fullHeal();
    void getRest();
    void switchTeam();
    vector<Pokemon> getPlayerParty();
    void setResult(bool win);
    bool playerResults();
    void levelUp(int index);
    void pokeDeath(int index);
    void takeDamage(int damage);
    void swapPokemon(int index);
    bool checkType();
    
    
    
    private:
    
    int points;
    int badges;
    int pokeballs;
    string username;
    string pokemon_name;
    Pokemon pokemon;
    int row;
    int index;
    int column;
    bool win;
    vector <Pokemon> player_pokemon;
    vector <Pokemon> pokedex;
    
};

#endif