#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "Game.h"

using namespace std;

    //introduction
    
Game :: Game (string map_file)
{
    vector<Pokemon> all_pokemon;
    
    map.readMap(map_file);
    
}

void Game :: readPokemon(string pokemon_file)
{
   ifstream pokemon_list;
    pokemon_list.open(pokemon_file);
    string line = "";
    string temp[9];
    
    while (getline (pokemon_list, line))
    {
        if (line != "" && line[0] != '#')
        {
            temp[8] = "";
            split(line, char(44), temp, 9); //splits all values of a single pokemon
            Pokemon pkmn = Pokemon(temp);
            all_pokemon.push_back(pkmn); //adds entire object into all pokemon vector
        }
    }
    pokemon_list.close();
}


void Game :: introduction()
{
    string username;
    string starter_choice;
    int starter;
    bool chosen = false;
    
    cout << "Welcome to the world of Pokemon!" << endl;
    cout << "Please enter your name: " << endl;
    getline(cin, username);
    player.setName(username);
    
    cout << endl;
    cout << "Welcome, " << username << "!" << endl;
    cout << "Before you can begin your adventure, you must choose a starting Pokemon, courtesy of the Professor" << endl;
    
    while(!chosen)
    {
        cout << "Please choose from the following Pokemon: " << endl;
        cout << "1. Bulbasaur" << endl;
        cout << "2. Charmander" << endl;
        cout << "3. Squirtle" << endl;
        cout << "4. Pikachu" << endl;
        getline (cin, starter_choice);
        
        switch(starter_choice[0])
        {
            case '1': //choose Bulbausaur
            player.addPokemon(all_pokemon[0]);
            player.setLocationRow(12);
            player.setLocationCol(6);
            chosen = true;
            break;
            
            case '2': //Charmander
            player.addPokemon(all_pokemon[3]);
            player.setLocationRow(12);
            player.setLocationCol(7);
            chosen = true;
            break;
            
            case '3': //Squirtle
            player.addPokemon(all_pokemon[6]);
            player.setLocationRow(12);
            player.setLocationCol(8);
            chosen = true;
            break;
            
            case '4': //Pikachu
            player.addPokemon(all_pokemon[24]);
            player.setLocationRow(12);
            player.setLocationCol(9);
            chosen = true;
            break;
            
            default:
            cout << "Please choose a valid option" << endl;
            break;
        }
    }
    
    cout << endl;
    cout << "A fantastic choice! She looks happy to be your new partner!" << endl;
    cout << "Now, here are a few Pokeballs to begin your journey." << endl;
    
    cout << "You received 10 Pokeballs!" << endl;
    cout << "There is a long road ahead. But I believe you and your Pokemon will be able to overcome anything!" << endl;
    cout << endl;

}

void Game :: choiceMenu() //four choices: travel, rest, try luck, or quit
{
    string choice;
    string direction;
    
    while (choice[0] != '4') //while you do not quit
    {

        cout << "Good morning! Today is a wonderful day!"<< endl;
        cout << "You currently have " << player.getPokeballs() << " Pokeballs and your Pokemon are happy!" << endl;
        cout << "- - - - - - -" << endl;
        player.viewActivePokemon();
        
        cout << "- - - - - - - " << endl;
        cout << "1. Travel" << endl;
        cout << "2. Rest" << endl;
        cout << "3. Try your Luck" << endl;
        cout << "4. Quit" << endl;
        getline(cin, choice);
        
        switch(choice[0])
        {
            case '1':
            {
                cout << "Where would you like to go? Choose from W, A, S, D." << endl;
                cout << "North (w)" << endl;
                cout << "West (a)" << endl;
                cout << "East (d)" << endl;
                cout << "South (s)" << endl;
                getline(cin, direction);
            
                map.travel(&player, direction[0]);
                
                if (map.checkCenterLocation(player) == true) //if player is on Center tile
                {
                    map.centerMenu(&player);
                }
                int wildIndex = map.findWildPKMN(&player); 
                if (wildIndex>=0)
                {
                    battleWild(wildIndex);
                }
                break;
            }
            case '2': 
            {
                player.getRest(); //at the cost of one pokeball each pokemon gains 1 health point
                break;
            }
            
            case '3':
            {
                map.tryLuck(&player);
                break;
            }
            
            case '4':
            {
                cout << "Thank you for playing!" << endl;
                quit();
                break;
            }
        }
        if (choice[0] != '4')
        {
            map.moveWild();
            map.displayMap(&player);
            if (player.checkType() == true)
            {
                cout << "You found at least 8 different types of Pokemon! You win! Congrats!" << endl;
                quit();
                break;
            }
            hidden_treasure();
            death();
            
        }
    }
}

void Game :: displayMap()
{
    map.displayMap(&player);
}

void Game :: travel(char direction)
{
    map.travel(&player, direction);
}

void Game :: initializeWild()
{
   map.initializeWild(all_pokemon);
}

void Game :: assignWild()
{
    map.assignWild();
}

void Game :: moveWild()
{
    map.moveWild();
}

void Game :: initializeTrainers()
{
    map.initializeTrainers(all_pokemon, &trainers);
}

void Game :: findWild()
{
    map.findWildPKMN(&player);
}

void Game :: gymMenu(Player player)
{
    if (map.checkGymLocation(player) == true)
        {
            int index;
            for (int k = 0; k < 15; k++)
            {
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 25; j++)
                    {
                        if (i == trainers[i].getTrainerRow() && j == trainers[i].getTrainerCol())
                        {
                            index = k;
                        }
                    }
                }
            }
            cout << "You arrived at the Gym!" << trainers[index].getTrainerName() << " wishes to challenge you!" << endl;
            cout << "Their Active Pokemon is: " << endl;
            
        }
    }


string Game :: rest() //heals pokemon by 1 point at the cost of 1 pokeball
{
    player.getRest();
}
    
    //battle
void Game :: battleWild(int wildIndex)
{
    srand(time(nullptr));
    string choice;
    string switchChoice;
    int switchNum;
    Pokemon temp[1];
    bool fightEnd = false;
    
    int playerSpeed = player.getPlayerParty()[0].getSpeed();
    int playerAttack = player.getPlayerParty()[0].getAttack();
    int playerDefense = player.getPlayerParty()[0].getDefense();
    
    int wildSpeed = map.getWildPokemon(wildIndex).getSpeed();
    int wildAttack = map.getWildPokemon(wildIndex).getAttack();
    int wildDefense = map.getWildPokemon(wildIndex).getDefense();
    bool playerFirst = playerSpeed > wildSpeed;
    
    cout << "You ran into a wild pokemon!" << endl;
    cout << endl;
    while (fightEnd == false)
    {
        map.getWildPokemon(wildIndex).getStats();
        player.getPlayerParty()[0].getStats();
        cout << endl;
        cout << "What do you want to do? Choose from 1, 2, or 3." << endl;
        cout << "1. Fight" << endl;
        cout << "2. Switch Active Pokemon" << endl;
        cout << "3. Run" << endl;
        getline(cin, choice);
        
        int wildFlee = rand() % 5; //choose from 0 to 4. 60% chance, or 3 out of 5
       
        bool wildFirst = wildSpeed > playerSpeed;
        
        switch (choice[0])
        {
            case '1': 
            {
                if (wildFlee == 0 || wildFlee == 1 || wildFlee == 2) //wild pokemon will attack
                {
                    if (playerFirst) //if player speed is greater than wild, player can attack first
                    {
                        int playerA = rand() % playerAttack + 1;
                        int wildD = rand() % wildDefense + 1;
                        int damage = playerA - wildD;
                        
                        if (damage > 0)
                        {
                            cout << player.getPlayerParty()[0].getName() << " dealt " << damage << " damage." << endl;
                            map.takeDamageWild(wildIndex, damage);
                        }
                        else
                        {
                            cout<< player.getPlayerParty()[0].getName() << " missed!" <<endl; //if the damage is not over 0
                        }
                    }
                    else
                    {
                        int playerD = rand() % playerDefense + 1;
                        int wildA = rand() % wildAttack + 1;
                        int damageWild = wildA - playerD;
                        if (damageWild > 0) //attack is greater than defense
                        {
                            cout << map.getWildPokemon(wildIndex).getName() << " dealt " << damageWild << " damage." << endl;
                            player.takeDamage(damageWild); //change player pokemons health 
                        }
                        else
                        {
                            cout<< map.getWildPokemon(wildIndex).getName() << " missed!" <<endl; //no damage
                        }
                    }
                    playerFirst = !playerFirst; //if player speed is greater, first turn player goes, and forces wild to fight on second turn and continues switching
                    
                    if (map.getWildPokemon(wildIndex).getCurrentHealth() == 0)
                    {
                        cout << "You defeated " << map.getWildPokemon(wildIndex).getName() << "! It will join your party or Pokedex." << endl;
                        player.addPokemon(map.getWildPokemon(wildIndex)); //add the pokemon to the party or pokedex
                        player.setPokeballs(player.getPokeballs()-1); //subtract 1 pokeball
                        player.setPoints(player.viewPoints() + 10); //add 10 points
                        map.deleteWild(wildIndex);
                        fightEnd = true;
                    }
                    
                    bool flag = true;
                    for (int i = 0; i < player.getPlayerParty().size(); i++)
                    {
                        if (player.getPlayerParty()[i].getCurrentHealth() != 0)
                        {
                            flag = false; //pokemon have health and are not all dead
                        }
                    }
                    
                    if(flag)
                    {
                        cout << "All of your Pokemon have fainted!" << endl; //all pokemon don't have any health
                        fightEnd = true;
                    }
                    if (player.getPlayerParty().size() > 1 && player.getPlayerParty()[0].getCurrentHealth() == 0)
                    {
                        cout << "Oh no, your Pokemon fainted!" << endl;
                        string choice;
                        int choiceNum;
                        while(true)
                        {
                            cout << "Pick another Pokemon to be your Active Pokemon." << endl;
                            
                            for (int i = 1; i < player.getPlayerParty().size(); i++) //does not include current active pokemon
                            {
                                cout << i << ". " << player.getPlayerParty()[i].getName() << endl;
                            }
                            
                            getline(cin, choice);
                            choiceNum = stoi(choice);
                            
                            if (player.getPlayerParty()[choiceNum].getCurrentHealth() == 0) //does not allow user to choose pokemon with 0 health
                            {
                                cout << "Please choose a Pokemon who has not fainted." << endl;
                            }
                            else
                            {
                                break;
                            }
                        }
                        player.swapPokemon(choiceNum); //swap pokemon with active and chosen
                        cout << player.getPlayerParty()[0].getName() << " is now the Active Pokemon!" << endl;
                
                    }
                    
                }
                
                else
                {
                    if (wildFirst)
                    {
                        cout << "Oh, that's unfortunate. The wild Pokemon escaped!"<< endl;
                        map.teleportWild(wildIndex); //teleport to random location
                        fightEnd = true;
                    }
                    else
                    {
                        cout << map.getWildPokemon(wildIndex).getName() << " tried to flee but it failed!" << endl; //stays in the battle but tried to flee
                    }
                }
                break;
            }
            
            case '2':
            {
                string choice;
                int choiceNum;
                while(true)
                {
                    cout << "Pick another Pokemon to be your Active Pokemon." << endl;
                    
                    for (int i = 1; i < player.getPlayerParty().size(); i++)
                    {
                        cout << i << ". " << player.getPlayerParty()[i].getName() << endl;
                    }
                    
                    getline(cin, choice);
                    choiceNum = stoi(choice);
                    
                    if (player.getPlayerParty()[choiceNum].getCurrentHealth() == 0)
                    {
                        cout << "Please choose a Pokemon who has not fainted." << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                player.swapPokemon(choiceNum);
                cout << player.getPlayerParty()[0].getName() << " is now the Active Pokemon!" << endl;
                
                
                break;
            }
            case '3': 
            {
                int escapeCount = 1;
               
                if (playerSpeed > wildSpeed)
                {
                    cout << "You successfully escaped!" << endl;
                    map.teleportWild(wildIndex);
                    fightEnd = true;
                    break;
                }
                else
                {
                    double A = playerSpeed * 32;
                    double B = (wildSpeed / 4) % 256;
                    double F = ((A / B) + 30) * escapeCount;
                    
                    if (F > 255)
                    {
                        cout << "You successfully escaped!" << endl;
                        cout << "You will be sent to the nearest Pokemon Center." << endl;
                        map.teleportWild(wildIndex);
                        fightEnd = true;
                        break;
                    }
                    else
                    {
                        int chance = rand() % 255;
                        if (chance > F)
                        {
                            cout << "You successfully escaped!" << endl;
                            cout << "You will be sent to the nearest Pokemon Center." << endl;
                            fightEnd = true;
                            break;
                        }
                        else if (chance < F)
                        {
                            cout << "You could not escape..." << endl;
                            escapeCount++;
                        }
                    }
                }
            }
        }
    }
}


void Game :: quit()
{
    ofstream results_file;
    results_file.open("resultsPokemon.txt", ios::out | ios::app);

    
    results_file << player.getName() << "      " << "Maybe you won? I don't know." << "      " << player.viewPoints() << endl;
}

void Game :: battleGym()
{
    
}

string Game :: switch_active(int pokemon_number)
{
    //prompt user to switch from pokemon in active pokemon array (not pokedex); 
}

    //random events
void Game :: second_wild() //30% chance another one appears after initial encounter
    {
        //only after catching a wild pokemon, sees if there is another one nearby for second chance
    }
    
void Game :: hidden_treasure() //25% chance of finding (50/50 for pokeball or poffin)
{
    srand(time(nullptr));
    int chance = rand() % 4;
    int chanceItem = rand() % 2; //choose 0 or 1
    string choice;
    int choiceNum;
    
    if (chance == 0)
    {
        if (chanceItem == 0) //half chance
        {
            cout << "What a lucky day! You found a hidden stash of 2 Pokeballs!" << endl;
            player.setPokeballs(player.getPokeballs() + 2);  //adds 2 pokeballs
            cout << "You now have " << player.getPokeballs() << " Pokeballs!" << endl;
            
        }
        else if (chanceItem == 1) //other half
        {
            cout << "Amazing! You have found a delicious Poffin! Choose one of your Pokemon in your party to feast on this treat and level up!" << endl;
            player.viewActivePokemon(); //lists pokemon
            getline(cin, choice);
            choiceNum = stoi(choice);
            player.levelUp(choiceNum - 1); //levels up pokemon at index (whatever user chooses minus 1 due to indexing)
        }
    }
}

void Game :: death() //20% chance of one pokemon dying
{
   srand(time(nullptr));
   int deathChance = rand() % 5; //20% chance, or 1 out of 5
   int pokemonIndex = rand() % player.getPlayerParty().size(); //randomly choose one pokemon from party
   
   if (player.getPlayerParty().size() == 1) //if there is one pokemon in your party, cannot kill it off
   {
       deathChance = 1; //only if deathChance is 0, can the pokemon die
   }
   
   if (deathChance == 0)
   {
        cout << "Oh no! " << player.getPlayerParty()[pokemonIndex].getName() << " has died of old age. Rest in peace, my friend." << endl;
        player.pokeDeath(pokemonIndex); //delete from party vector and shift up
       
   }
}
    
    
  