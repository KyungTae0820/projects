#include <iostream>
#include <fstream>


using namespace std;

// prototypes
void sort(int data[], int len);
int binsearch(int target, int data[], int start, int end);

int main(int argc, char *argv[]){
  int target;
  if(argc < 3){
    cout << "Provide a filename of the data to be searched." << endl;
    cout << "And also provide a target number to search for." << endl;
    return 1;
  }
  ifstream datfile(argv[1]);
  if( datfile.fail() ){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  int count = 0;
  // Count how many integers are in the file
  while(! datfile.fail()){
    int temp;
    datfile >> temp;
    if(!datfile.fail()){
      count++;
    }
  }
  // Reach the end of the file -> the EOF flag is set
  datfile.clear();
  //  Set internal position in the file back to 0
  //  Add a call to datfile.seekg() with appropriate arguments 
  //  to ensure the `datfile` stream returns to the beginning of the file
  datfile.seekg(0, ios::beg);

  // Now allocate an array to store the file data and read in the data
  int *data = new int[count];
  for(int i=0; i < count; i++){
    datfile >> data[i];
  }

  datfile.close();

  // Uncomment the line below for part 2
  sort(data, count);

  cout << "Read " << count << " integers from the data file." << endl;
  for(int i=0; i < count; i++){
    cout << data[i] << " ";
  }
  cout << endl;

  target = atoi(argv[2]); 
  cout << "Will now search for: " << target << endl;

  // Call binary search
  int retval = binsearch(target,data,0,count);

  // DO NOT ALTER - Interpret and print the results. 
  cout << "Binary search returned: " << endl;
  cout << retval << endl;

  // Deallocate the data array
  delete [] data;
  return 0;
}


// Returns the index in the data array where target is located
//  or -1 if the target value is not in the list
// Note: start is an inclusive index, while end is exclusive 
//       (i.e. 1 beyond the last data index to consider)
int binsearch(int target, int *data, int start, int end)
{
  if(start >= end){
    return -1;
  }
  int midPos = (start + end)/2;
  if(data[midPos] == target){
    return midPos;
  }
  else if(data[midPos] > target){
    return binsearch(target, data, start, midPos-1);
  }
  else{
    return binsearch(target, data, midPos+1, end);
  } 
}

// implements a selection sort algorithm to sort
//  the integer values in the 'data' array of size 'len'
void sort(int *data, int len)
{
   int idxCount = 0;
   if(len == 1){
     return;
   }
   int minVal = 100;
   int idx = 0;
   for(int i = 0; i < len; i++){
     if(data[i] < minVal){
       minVal = data[i];
       idx = i;
     }
   }
   int temp = data[idxCount];
   data[idxCount] = data[idx];
   data[idx] = temp;
   idxCount++;
   sort(data+1, len - 1);
}
