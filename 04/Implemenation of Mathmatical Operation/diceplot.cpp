#include <iostream>
#include <cstdlib>
using namespace std;

// Prototype/define functions 
int roll();
int calc();
void printHistogram(int counts[]);

int main()
{
  int seed, n;
  cin >> seed >> n;

  // Seed the pseudo-random number generator for repeatable results
  srand(seed);

  int counts[21];
  for(int i =0; i<21; i++){
    counts[i] = 0;
  }
  
  for(int i = 0; i < n; i++){
    int froll = calc();
    counts[froll-4] += 1;
  }
  printHistogram(counts);

  return 0;
}

int roll()
  {
    return (rand()%6) +1;
  }

  int calc()
  {
    return roll() + roll() + roll() + roll();
  }

  void printHistogram(int counts[])
  {
    for(int i = 0; i < 21; i++){
      cout << i+4 << ": ";
      for(int j = 0; j<counts[i]; j++){
        cout <<"X";
      } 
      cout << endl;
    }
  }