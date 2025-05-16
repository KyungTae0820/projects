#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void combination_recursion(std::string in, unsigned int dashIdx, std::string floating, 
                           const std::set<std::string>& dict, std::set<std::string>& guesses){
    if(dashIdx == in.size()){
        if(floating.empty()){
            if(dict.find(in) != dict.end()){
                guesses.insert(in);
            }
						return;
        }
    }
    if(in[dashIdx] == '-'){
        unsigned int blankloc = count(in.begin() + dashIdx, in.end(), '-');
        if(floating.size() < blankloc){
            for(unsigned int i = 0; i < floating.size(); i++){
                string tempGuess;
                string nextGuess;
                tempGuess = in;
                tempGuess[dashIdx] = floating[i];
                nextGuess = floating.substr(0, i) + floating.substr(i + 1);
                combination_recursion(tempGuess, dashIdx + 1, nextGuess, dict, guesses);
            }
            for(char i = 'a'; i <= 'z'; i++){
                if(floating.find(i) == string::npos){
                    in[dashIdx] = i;
                    combination_recursion(in, dashIdx + 1, floating, dict, guesses);
                    in[dashIdx] = '-';
                }
            }
        }
        else if(floating.size() == blankloc){
            for(unsigned int i = 0; i < floating.size(); i++){
                string tempGuess;
                string nextGuess;
                tempGuess = in;
                tempGuess[dashIdx] = floating[i];
                nextGuess = floating.substr(0, i) + floating.substr(i + 1);
                combination_recursion(tempGuess, dashIdx + 1, nextGuess, dict, guesses);
            }
        }
    }
    else combination_recursion(in, dashIdx + 1, floating, dict, guesses);
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> guesses;
    combination_recursion(in, 0, floating, dict, guesses);
    return guesses;
}

// Define any helper functions here
