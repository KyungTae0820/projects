// game.cpp
// Hangman game illustrates string library functions,
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype.
int processGuess(char *word, const char *targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string literals (e.g. "hi") evaluate to the starting address
//  of those characters(want an array of char *'s)
const char *wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn",
                          "science", "engineer"};

const int numWords = 10;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    srand(time(0)); // use the time to get randomly chosen words each run
  }
  else
  {
    srand(atoi(argv[1])); // use the command line argument as the seed
  }

  // Pick a random word from the wordBank
  const char *targetWord = wordBank[rand() % numWords];

  int numTurns = 10; // variable to track how many turns remain

  char word[80]; // a blank array to use to build up the answer
                 // It should be initialized with *'s and then
                 //  change them to the actual letters when the
                 //  user guesses the letter
  for (int i = 0; i < strlen(targetWord); i++)
  {
    word[i] = '*';
  }
  int c = strlen(targetWord); // not to make chunk after work
  word[c] = '\0';
  //cout << targetWord << endl; //6pbfj4fl
  // More initialization code as needed
  bool running = true;
  char userGuess;
  while (running)
  {
    cout << numTurns << " guesses remain: " << endl;
    cout << "Enter a letter: " << word <<endl;
    cin >> userGuess;
    // Populating variable that contains user guessed word
    if (numTurns > 0)
    {
      if (userGuess != '!')
      {
        int k = processGuess(word, targetWord, userGuess);
        if (strcmp(word, targetWord) == 0)
        {
          cout << "Win! " << numTurns << " guesses to spare." << endl;
          running = false;
        }
        else if(k == 0){
            numTurns -= 1;
            if(numTurns == 0){
              cout << "Lose! " << word << endl;
              running = false;
            }
        }
      }
      else
      {
        cout << "Quit!" << endl;
        running = false;
      }
    }

    // The game should continue until a word
    //  is guessed correctly, a '!' is entered,
    //  or 10 turns have elapsed without the word being guessed

    // Print out end of game status
  }
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char *word, const char *targetWord, char guess)
{
  int count = 0;
  for (int i = 0; i < strlen(targetWord); i++)
  {
    if (targetWord[i] == guess && word[i] != guess)
    {
      word[i] = guess; 
      count += 1;
    }
  }
  return count;
}