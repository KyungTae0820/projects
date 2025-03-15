// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, and dynamic allocation, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Seed the random number generator (RNG) with user-provided seed or
//  current time.
// @param [in] seedarg - NULL, if no seed was provided on the command line
//                       or pointer to the C-string containing the seed.
void seedRNG(char* seedarg);

int main(int argc, char* argv[]) {
  int numWords;
  ifstream ifstr(argv[1]);
  ifstr >> numWords;
  char** wordBank = new char* [numWords];

  if(argc > 3 || argc < 2){
    return 1;
  }
  else if(argc == 2){
    if(ifstr.fail()){
      return 2;
    }
    seedRNG(NULL);
  } 
  else if(argc == 3){
    if(ifstr.fail()){
      return 2;
    }
    seedRNG(argv[2]);
  }

  for(int i = 0; i < numWords; i++){
    char buff[41];
    ifstr >> buff;
    int len = strlen(buff);
    wordBank[i] = new char[len+1];
    strcpy(wordBank[i], buff);
  }
  ifstr.close();
  //More variables for later
  char guess[80] = "";     // blank array for user input
  bool wordGuessed = false;
  int numTurns = 10; 
    
  //Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);
  cout << "Sol: " << wordBank[target] << endl;
  char* word = NULL;  // pointer to target word

  word = new char[targetLen+1];//'\0'때문에 +1을 해줘야함. 깜빡하고있었네!!!!
  strcpy(word, wordBank[target]);
  permute(word, targetLen);

  // An individual game continues until '!' is entered, a word
  //  is guessed correctly or 10 turns have elapsed
  while (guess[0] != '!' && !wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? " << endl;
    cin >> guess;
    if(strcmp(guess, wordBank[target]) == 0){
        wordGuessed = true;
    }
    numTurns--;   // Every guess counts as a turn
  }
  delete [] word;////여기서 word array한번 삭제를 함.

  if(guess[0] == '!'){
    cout << "Quit!" << endl;
  }
  else if(wordGuessed){
    cout << "Win! " << numTurns << " guesses to spare." << endl;
  }
  else {
    cout << "Lose! " << wordBank[target] << endl;
  }
  for(int i = 0; i < numWords; i++){
    delete [] wordBank[i];
  }
  delete [] wordBank;
  
  return 0;
}

// Scramble the letters. Uses "Knuth shuffle" algorithm.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

// Seed the RNG 
void seedRNG(char* seedarg)
{
  if(NULL == seedarg){
    srand(time(0)); // use the time to get randomly chosen words each run
  }
  else {
    srand(atoi(seedarg)); // use the command line argument as the seed
  }
}
