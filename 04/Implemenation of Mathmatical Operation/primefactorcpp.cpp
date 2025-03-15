#include <iostream>
using namespace std;
int main(){
  int i;
  int x;
  int count2=0;
  int count3 = 0;
  cout << "Enter a positive integer: " << endl;

  cin >> x;

  if(x <= 1){
    cout << "NO" << endl;
    return 0;
  }

  for(i = 2; i <=x; i++){
    while(x%i == 0){
        if(i==2){
          x /= i;
          count2++;
          if(x == 1){
            break;
          }
        }
        else if(i==3){
          x /=i;
          count3++;
          if(x == 1){
            break;
          }
        }
        else{
          x /= i;
        } 
      } 
    }

  if(i>=5){
    cout << "No" << endl;
  }
  else{
    cout << "Yes" << endl;
    cout << "Twos=" << count2;
    cout << " Threes=" << count3;
  }
  return 0;
}