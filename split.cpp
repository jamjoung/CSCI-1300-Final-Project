#include <iostream>
#include <string>
using namespace std;


int split(string parameter, char delimiter, string array[], int length)
{
    string temp = ""; //temp
    int split_pieces = 0;
    parameter = parameter + delimiter; //allows last word to be accounted for
    int n = 0; //for each string wtihin array
    
    
    if (parameter.length() == 0)
    {
        return 0;
    }
    
    else if (parameter.length() > 0)
    {
        if (parameter[0] == delimiter)
            {
                parameter.erase(0, 1); //gets rid of delimiter in the beginning of 
                
            }
            
        for (int i = 0; i < parameter.length(); i++)
        {
            
            
            if (parameter[i] != delimiter) //does not equal delimiter, will add onto temp string
            {
                temp = temp + parameter[i];
            }
            
            else if (parameter[i] == delimiter && parameter[i+1] == delimiter) //two delimiters in a row. erase both
            {
                parameter.erase (i, 1);
                split_pieces++;
                array[n] = temp;
                n = n + 1;
                temp = "";
                 
            }
            else if (parameter [i] == delimiter && parameter[i+1] != delimiter) //only one delimiter
            {
               parameter.erase (i, 0);
                split_pieces++;
                array[n] = temp;
                n = n + 1; //so next array is array[n+1]
                temp = ""; //reset temp
            }
            
            
        }
       
        
        if (split_pieces > length)
        {
            return -1;
        }
        else
        {
            return split_pieces; 
        }
            
    }
         
} 