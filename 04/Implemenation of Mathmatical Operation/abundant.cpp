#include <iostream>
using namespace std;

//ADDED function that calculates the sum of divisor
int sumx = 0;
int factor(int x){
  for(int l = 1; l<= x/2; l++){
    if(x%l == 0){
      sumx = sumx + l;
    }
  }
  return sumx;
}

int main()
{
  // n1 is the number with the highest abundance, a1
  // n2 is the number with the 2nd-highest abundance, a2
  // n3 is the number with the 3rd-highest abundance, a3
  unsigned int n1 = 0, n2 = 0, n3 = 0;
  int a1 = 0, a2 = 0, a3 = 0;

  // num_abundant counts how many numbers in the input
  // sequence are abundant
  int num_abundant = 0;

  cout << "Enter a sequence of natural numbers, separated by spaces, ";
  cout << "and ending with 0."<< endl;

  int num;
  int i =0;
  int iarr[10] = {0,0,0,0,0,0,0,0,0,0};  //int arr: divisor sum of num
  int oarr[10] = {0,0,0,0,0,0,0,0,0,0}; //orignial num
  int count = 0;
  int temp1 = 0;
  int temp2 = 0;

//receive values
  while (num != 0){
      cin >> num;

      if(factor(num) > num){
         oarr[i] = num; 
         iarr[i] = factor(num);
         num_abundant++;
         count++;
         i++;
      }
      sumx = 0;
  }

//change order
  for(i = 0; i<count-1; i++){
    for(int j = i+1; j<count; j++){
      if(iarr[i] < iarr[j]){
        temp1 = iarr[i];
        temp2 = oarr[i];

        iarr[i] = iarr[j];
        oarr[i] = oarr[j];

        iarr[j] = temp1;
        oarr[j] = temp2;
      }
    }
  }

  n1 = oarr[0];
  n2 = oarr[1];
  n3 = oarr[2];

  a1 = iarr[0]/2;
  a2 = iarr[1]/2;
  a3 = iarr[2]/2;
  
  
  cout << "Abundant number count: " << num_abundant << endl;
  cout << "Top 3 most abundant numbers: " << endl;
  cout << n1 << " : " << a1 << endl;
  cout << n2 << " : " << a2 << endl;
  cout << n3 << " : " << a3 << endl;


  return 0;

}