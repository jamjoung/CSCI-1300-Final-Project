#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
#include <stdexcept>

Player :: Player()
{
    username = "";
    points = 0;
    pokeballs = 10;
    vector<Pokemon> player_pokemon;
    
}

void Player :: addPokemon(Pokemon pokemon) //adds to party
{
    if (player_pokemon.size() < 6)
    {
        player_pokemon.push_back(pokemon);
    }
    
    pokedex.push_back(pokemon);
}

void Player :: viewActivePokemon() //lists all pokemon in party
{
    cout << "Your Active Pokemon is : " << endl;
    for (int i = 0; i < player_pokemon.size(); i++)
    {
         
    cout << i + 1 <<  ". Name: " << player_pokemon[i].getName(); //i + 1 so it doesn't start at 0;
    cout << ", HP: " << player_pokemon[i].getCurrentHealth();
    cout << ", A: " << player_pokemon[i].getAttack();
    cout << ", D: " << player_pokemon[i].getDefense();
    cout << ", S: " << player_pokemon[i].getSpeed();
    cout << ", M: " << player_pokemon[i].getMax();
    
    cout << endl;
    }
}

vector<Pokemon> Player :: getPlayerParty()
{
    return player_pokemon;
}

void Player :: setPoints(int numPoints)
{
    points = numPoints;
}

int Player :: viewPoints()
{
    return points;
}

void Player :: setName(string name)
{
    username = name;
}
string Player :: getName()
{
    return username;
}


void Player :: setLocationRow(int row1)
{
    row = row1;
}
int Player :: getLocationRow()
{
    return row;
}
void Player :: setLocationCol(int column1)
{
    column = column1;
}
int Player :: getLocationCol()
{
    return column;
}

void Player :: setPokeballs(int ball)
{
    pokeballs = ball;
}
int Player :: getPokeballs()
{
    return pokeballs;
}
void Player :: setBadges(int badgeNum)
{
    badges = badgeNum;
}
int Player :: getBadges()
{
    return badges;
}

void Player :: fullHeal() //for pokemon centers
{
    for (int i = 0; i < player_pokemon.size(); i++)
    {
        if (player_pokemon[i].getCurrentHealth() < player_pokemon[i].getMaxHealth()) //if the current health is less than max, replace so it is at full health
        {
            player_pokemon[i].setCurrentHealth(player_pokemon[i].getMaxHealth());
        }
    }
}

void Player :: getRest() //to heal 1 HP from the game menu
{
    if (getPokeballs() > 0) //only if there are available pokeballs to spend
    {
        setPokeballs(getPokeballs() - 1); //subtract 1
        for(int i = 0; i < player_pokemon.size(); i++)
        {
            {
                if (player_pokemon[i].getCurrentHealth() < player_pokemon[i].getMaxHealth())
                {
                    player_pokemon[i].setCurrentHealth(player_pokemon[i].getCurrentHealth() + 1);
                }
            }
        }
    }
    else
    {
        cout << "You have insufficient Pokeballs. Sorry! You will suffer." << endl;
    }
}

void Player :: switchTeam()
{
    while(player_pokemon.size())
    {
        player_pokemon.pop_back(); //empty out player's party
    }
    
    int choiceNum = 0;
    string pokeNum;
    int pokeNumber = 0;
    string numbers;
    int tempNum[6];
    
    do {
        cout << "Here are all the Pokemon in your Pokedex." << endl;
         
        for (int i = 0; i < pokedex.size(); i++)
        {
            cout << i+1 << "." << pokedex[i].getName() << endl; //all pokemon are in the pokedex
        }
    
        cout << "Who would you like to take out? Please list the Pokemon you wish to take out separated by spaces." << endl;
        int pokedexPosition[6] = {-1, -1, -1, -1, -1, -1}; //make everything invalid first (so if you choose less than 6, it only counts valid numbers)
        string temp[6];
        getline(cin, numbers);
        int numberChoices = split(numbers, ' ', temp, 6); //separates each choice by a space
        
        for (int k = 0; k < numberChoices; k++)
        {
            try
            {
                pokedexPosition[k] = stoi(temp[k]); //the user's input number is stored in here
                for (int i = 0; i < k; i++)
                {
                    if (pokedexPosition[k] == pokedexPosition[i]) //if it matches
                    {
                        pokedexPosition[i] = 0;
                    }
                }
            }
            catch (invalid_argument&e) //if the invalid argument appears, just set the pokedexPosition to 0
            {
                pokedexPosition[k] = 0;
            }
            
        }
        for (int i = 0; i < 6; i++)
        {
            if(pokedexPosition[i] > 0 && pokedexPosition[i] <= pokedex.size())
            {
                player_pokemon.push_back(pokedex[pokedexPosition[i]-1]); //subtract one from pokedex position because index starts at 0
            }
        }
        
        if(player_pokemon.size()==0)  //nothing was added to the party
        {
            cout << "You...didn't choose any valid Pokemon," << this -> getName() << "... Try again!" << endl;
        }
    }
    
    while(player_pokemon.size()==0); //everything above occurs if the party remains empty (so the last if check forces you to choose at least 1 pokemon)
    
    cout << "Here are the Pokemon now in your party!" << endl;
    for (int i = 0; i < player_pokemon.size(); i++)
    {
        cout << player_pokemon[i].getName() << endl;
    }
}

void Player :: swapPokemon(int index)
{
    Pokemon temp[1];
    
    temp[0] = player_pokemon[0];
    player_pokemon[0] = player_pokemon[index];
    player_pokemon[index] = temp[0];
}

void Player :: levelUp(int index) //parameter is the index of the pokemon in the party vector that levels up
{
    bool fullhp = player_pokemon[index].getCurrentHealth() == player_pokemon[index].getMaxHealth();
    player_pokemon[index].setMaxHealth(round(player_pokemon[index].getMaxHealth() * 1.02)); //max health and speedincreases regardless of the max value
    
    if (fullhp == true)
    {
        player_pokemon[index].setCurrentHealth(player_pokemon[index].getMaxHealth());
    }
    
    player_pokemon[index].setSpeed(round(player_pokemon[index].getSpeed() * 1.02));
    
    if (player_pokemon[index].getDefense() > player_pokemon[index].getMax()) //if the defense is initially greater than the max value, just keep it as is
    {
        player_pokemon[index].setDefense(player_pokemon[index].getDefense());
    }
    else if (round(player_pokemon[index].getDefense() * 1.02) < player_pokemon[index].getMax()) //if the new defense value is less than the max, set that as the new def
    {
        player_pokemon[index].setDefense(round(player_pokemon[index].getDefense() * 1.02));
    }
    
    else if (round(player_pokemon[index].getDefense() * 1.02 )>= player_pokemon[index].getMax()) //if the new defense value is or is greater than the max, set as the max (because it can't go over)
    {
        player_pokemon[index].setDefense(round(player_pokemon[index].getMax()));
    }
    
    
    
    if (player_pokemon[index].getAttack() > player_pokemon[index].getMax()) //if initial attack is greater than max, keep as is
    {
        player_pokemon[index].setAttack(player_pokemon[index].getAttack());
    }
    else if (round(player_pokemon[index].getAttack() * 1.02) < player_pokemon[index].getMax()) //if new attack value is less than max, set it as new attack
    {
        player_pokemon[index].setAttack(round(player_pokemon[index].getAttack() * 1.02));
    }
    else if (round(player_pokemon[index].getAttack() * 1.02) >= player_pokemon[index].getMax())// if new attack is greater or equal to max, set attack value as the max
    {
        player_pokemon[index].setAttack(round(player_pokemon[index].getAttack() * 1.02));
    }
}

void Player :: setResult(bool victory)
{
    win = victory;
}

bool Player :: playerResults()
{
    return win;
}

void Player :: pokeDeath(int index)
{
    player_pokemon.erase(player_pokemon.begin() + index); //at the index parameter, erase the pokemon that dies (chosen randomly in game function) from the vector and it will shift up the vector automatically
}
    
void Player :: takeDamage(int damage)
{
    player_pokemon[0].setCurrentHealth(player_pokemon[0].getCurrentHealth() - damage);
}

bool Player :: checkType()
{
    vector<string> type_array;
    for (int i = 0; i < pokedex.size(); i++)
    {
        string type1 = pokedex[i].getType1();
        string type2 = pokedex[i].getType2();
        bool type1_flag = true;
        bool type2_flag = true;
        
        for (int j = 0; j < type_array.size(); j++)
        {
            if (type1 == type_array[j])
            {
                type1_flag = false;
            }
            if (type2 == type_array[j])
            {
                type2_flag = false;
            }
        }
        
        if (type1_flag == false)
        {
            type_array.push_back(type1);
        }
        if (type2_flag == false)
        {
            type_array.push_back(type2);
        }
    }
    
    if (type_array.size() >= 8)
    {
        return true;
    }
    return false;

}