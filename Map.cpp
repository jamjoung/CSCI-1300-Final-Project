#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

Map :: Map()
{
    
}

void Map :: readMap(string map_file)
{
    string line = "";
    ifstream map;
    map.open(map_file);
    string temp[16];
    int i = 0;
    
    if (!map.fail())
    {
        while (getline(map, line))
        {
            if (line != "")
            {
                split(line, char(44), temp, 16);
                
                for (int j = 0; j < 16; j++)
                {
                    string tempChar = temp[j]; //
                    map_array[i][j] = tempChar[0];
                }
                i++;
            }
          
        }
    }
    
    
}

void Map :: displayMap(Player *playerPointer) //use pointer so it can be used with the player object defined in game class
{
   int col = playerPointer -> getLocationCol();  //x -> columns, y = rows
   int row = playerPointer -> getLocationRow();
   int colc = col; //column center
   int rowc = row;
   
   if (colc < 3) //column cannot be any smaller than 3 in order for map to be in the middle
   {
       colc = 3;
   }
   if (rowc < 3) //row cannot be any smaller than 3
   {
       rowc = 3;
   }
   
   if (rowc > 21) //opposite, row cannot be bigger than 21 (3 away from edge, at 24 (posiiton))
   {
       rowc = 21;
   }
   if (colc > 12) //column cannot be bigger than 12 (3 away from 15)
   {
       colc = 12;
   }
   
   for (int i = rowc - 3; i < rowc + 4; i++) //go through each row first
   {
       for (int j = colc - 3; j < colc + 4; j++) //in each row go through each column (go across the row)
       {
           if (row == i && col == j) //row and column are player's positions. if they are in the middle, than @
           {
               cout << "@";
           }
           else if (map_array[i][j] == "p") //land tiles are astericks
           {
                cout << "*";
           }
           else if (map_array[i][j] == "w") //water tiles are ~
           {
               cout << "~";
           }
           else
           {
               cout << map_array[i][j]; //leaves gyms and centers as G and C 
           }
       }
       cout << endl;
   }
}
    
bool Map :: travel(Player *playerPointer, char direction)
{
    int rows = playerPointer -> getLocationRow();
    int columns = playerPointer -> getLocationCol();
    
    switch(direction)
    {
        case 'w': //go up by subtracting one from row
            rows = rows - 1;
            break;
        
        case 'a': //go left by subtracting one from columns
           columns = columns - 1;
            break;
        
        case 's': //go down by adding 1 to a row
            rows = rows + 1;
            break;
       
        case 'd': //go right by adding one to column
            columns = columns + 1;;
            break;
        
        default:
        cout << "Choose a valid direction." << endl;
        break;
    }
    
    if (map_array[rows][columns] == "w") //if player tries go to on water, don't move and 
    {
        cout << "Please choose a different direction." << endl;
        return false;
    }
    
    if (rows < 0 || rows >= 25 || columns < 0 || columns >= 16) //if player tries to go out of bounds
    {
        cout << "Please choose a different direction." << endl;
        return false;
    }
    
    playerPointer -> setLocationCol(columns); //sets valid column
    playerPointer -> setLocationRow(rows); //sets valid rows
    return true;

}

void Map :: initializeWild(vector<Pokemon> all_pokemon)
{
    int i = 0;
    srand(time(nullptr));
    while (i < 20)
    {
        int number = rand() % 151; //choose one random number from 151
        for (int j = 0; j < 151; j++)
        {
            if (number != 1 && number != 4 && number != 7 && number != 25)
            {
                if (number == all_pokemon[j].getNumber()) //finds pokemon with same id number and is added to wild pokemon vector
                {
                    wild_pokemon.push_back(all_pokemon[j]); //adds pokemon object to vector of 20 wild pokemon
                }
            }
        }
        i++;
    }
}

void Map :: assignWild()
{
    int i = 0;
    srand(time(nullptr));
    
    while (i < 20)
    {
        int colcoord = rand() % 16; //random column
        int rowcoord = rand() % 25; //random row
        
        if (map_array[rowcoord][colcoord] == "p") //make sure that they can be put on a land tile (not any other one)
        {
            wild_pokemon[i].setLocationRow(rowcoord);
            wild_pokemon[i].setLocationCol(colcoord);
            i++; //only increment when wild pokemon are assigned to land tile
        }
    }
}

void Map :: teleportWild(int index)
{
    srand(time(nullptr));
    while(true)  //goes on until it hits the break
    {
        int colcoord = rand() % 16; //random column
        int rowcoord = rand() % 25; //random row
        
        if (map_array[rowcoord][colcoord] == "p") //make sure that they can be put on a land tile (not any other one)
        {
            wild_pokemon[index].setLocationRow(rowcoord);
            wild_pokemon[index].setLocationCol(colcoord);
            break;
        }
    }
}
    

void Map :: moveWild()
{
    srand(time(nullptr));
    int i = 0;
    while (i < 20)
    {
        int row = wild_pokemon[i].getLocationRow();
        int col = wild_pokemon[i].getLocationCol();
        bool moveTile = false;
        
        while (moveTile == false) //if pokemon cannot move, then it generates another number and goes through it again to move in a valid direction before incrementing
        {
            int move = rand() % 4;  //0 is up, 1 is left, 2 is down, 3 is right
            if (move == 0 && row - 1 >= 0 && map_array[row -1][col] == "p") //make sure the move is valid and not going out of bounds
            {
                wild_pokemon[i].setLocationRow(row - 1);
                moveTile = true; //move was legal, can move onto the next pokemon in the wild vector
            }
                
            else if (move == 1 && col - 1 >= 0 && map_array[row][col - 1] == "p")
            {
                wild_pokemon[i].setLocationCol(col - 1);
                moveTile = true;
            }
                
             else if (move == 2 && row + 1 <= 24 && map_array[row + 1][col] == "p")
             {
                wild_pokemon[i].setLocationRow(row + 1);
                moveTile = true;
                
             }
            
            else if (move == 3 && col + 1 <= 15 && map_array[row][col + 1] == "p")
            {
                wild_pokemon[i].setLocationCol(col + 1);
                moveTile = true;
            }
        }
        
        i++;
    }
}

void Map :: initializeTrainers(vector<Pokemon> all_pokemon, vector<Trainer> *trainerPointer)
{
    trainerPointer->push_back(Trainer("Claude", 1, 7));
    trainerPointer->push_back(Trainer("Forrest", 1, 14));
    trainerPointer->push_back(Trainer("Dimitri", 3, 2));
    trainerPointer->push_back(Trainer("Ayr", 4, 12));
    trainerPointer->push_back(Trainer("Taryn", 7, 16));
    trainerPointer->push_back(Trainer("Corrin", 8, 1));
    trainerPointer->push_back(Trainer("Moira", 10, 8));
    trainerPointer->push_back(Trainer("Shima", 11, 11));
    trainerPointer->push_back(Trainer("Mercedes", 12, 16));
    trainerPointer->push_back(Trainer("Kendall", 13, 2));
    trainerPointer->push_back(Trainer("Raihan", 17, 1));
    trainerPointer->push_back(Trainer("Lio", 19, 8));
    trainerPointer->push_back(Trainer("Coco", 21, 12));
    trainerPointer->push_back(Trainer("Skari", 22, 6));
    trainerPointer->push_back(Trainer("Sylvain", 23, 1));
    
    
    srand(time(nullptr));
    for (int i = 0; i < trainerPointer->size(); i++)    
    {
        int numPokemon = rand() % 6 + 1;  //randomly from 1-6 pokemone
        for (int j = 0; j < numPokemon; j++)
        {
            int number = rand() % 151 + 1;
            (*trainerPointer)[i].addPKMN(all_pokemon[j]); //adds the random pokemon to the trainer in the gyms
        }
          
    } 
}

void Map :: setWildBool(bool encounter)
{
    wild_encounter = encounter;
}
bool Map :: getWildBool()
{
    return wild_encounter;
}

int Map :: findWildPKMN(Player *playerPointer)
{
    int playerRow = playerPointer -> getLocationRow();
    int playerCol = playerPointer -> getLocationCol();
    
    for (int i = 0; i < wild_pokemon.size(); i++)  //checks the wild pokemon row and column in comparison to player's location
    {
        if (playerRow - 2 <= wild_pokemon[i].getLocationRow() && playerRow + 2 >= wild_pokemon[i].getLocationRow() && playerCol + 2 >= wild_pokemon[i].getLocationCol() && playerCol - 2 <= wild_pokemon[i].getLocationCol())
        {
            Pokemon wild_poke = wild_pokemon[i];
            this -> setWildBool(true);
            return i;
        }
         
    }
    return -1;
}

void Map :: tryLuck(Player *playerPointer)
{
    int row = playerPointer -> getLocationRow();
    int col = playerPointer -> getLocationCol();
    int rowc = row;
    int colc = col;
    srand(time(nullptr));
    int chance = rand() % 2;
    
    if (chance == 0) //50% chance of catching 
    {
        for (int i = 0; i < wild_pokemon.size(); i++)
        {
            //inside the 7 by 7 map, checks to see if both row and column of wild pokemon fall in there
            if (row - 7 <= wild_pokemon[i].getLocationRow() && row + 7 >= wild_pokemon[i].getLocationRow() && col - 7 <= wild_pokemon[i].getLocationCol() && col + 7 >= wild_pokemon[i].getLocationCol())
            {
                cout << "A wild " << wild_pokemon[i].getName() << " has appeared!" << endl;
                playerPointer -> addPokemon(wild_pokemon[i]);
                cout << wild_pokemon[i].getName() << " was caught!" << endl;
                wild_pokemon.erase(wild_pokemon.begin() + i);
                // playerPointer -> setPoints(playerPointer -> getPoints() + 10)
                return;
            }
        }
    }
    
    cout << "Sorry, you failed to catch a Pokemon. Try again next time!" << endl;
    
}

bool Map :: checkGymLocation(Player player)
{
    int row = player.getLocationRow();
    int col = player.getLocationCol();
    
    if (map_array[row][col] == "G")
    {
        return true;  //if its true can return the gym menu in the game
    }
    return false;
}

bool Map :: checkCenterLocation(Player player)
{
    int row = player.getLocationRow();
    int col = player.getLocationCol();
    
    if (map_array[row][col] == "C")
    {
        return true; //if true it returns the center menu when checked in the game
    }
    return false;
}


void Map :: centerMenu(Player *playerPointer)
{
    string choice;
    
    if (checkCenterLocation(*playerPointer) == true)
    {
        cout << "Welcome to the Pokemon Center! All pokemon in your party have been healed." << endl;
        playerPointer -> fullHeal(); //heals all pokemon to full health in the party
         
        cout << "Do you want to change the members of your party?" << endl;
        cout << "Y" << endl;
        cout << "N" << endl;
        getline(cin, choice);
        if (choice == "y" || choice == "Y")
        {
            playerPointer -> switchTeam(); //allows opportunity to reselect team
        }
        else if (choice == "n" || choice == "N")
        {
            cout << "You're good to go! Have a nice day!" << endl; //leaves 
        }
        
    }
}

void Map :: statsWild(int index)
{
}

void Map :: takeDamageWild(int index, int damage)
{
    wild_pokemon[index].setCurrentHealth(wild_pokemon[index].getCurrentHealth() - damage); //sets the health of the wild pokemon after taking damage
}
Pokemon Map :: getWildPokemon(int index)
{
    return wild_pokemon[index]; //returns single wild pokemon from vector
}
void Map :: deleteWild(int index)
{
    wild_pokemon.erase(wild_pokemon.begin() + index); //deletes wild after being caught
}
void Map :: swapPokemon() //switches pokemon from pokedex at center
{
    //asks user if pokemon wants to be swapped
    //lists pokedex (viewpokedex()), numbered
    //user inputs up to 6 pokemon and takes from pokedex array
}

/*void Map :: healPokemon() //heals party if user is at center
{
    for (int i = 0; i < player_pokemon.size(); i++)
    {
        player_pokemon[i].setCurrentHealth(getMaxHealth());
    }
}
*/
void Map :: teleportTrainer() //if trainer is defeated, teleport to nearest center
{
    //after losing a battle, calculate the closest center to teleport trainer and heals pokemon 
    //redefines current position so they start at the center next turn
}
    
    //gym

void Map :: battleGym() //enters battle only if there is a trainer at the gym (cannot flee)
{
    
}
