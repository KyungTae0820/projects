#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> converted_rawWord;
  stringstream s1(rawWords);
  int len = rawWords.size();
  for(int i = 0; i < len; i++){
    if(!ispunct(rawWords[i])){
      //cout << "parseStringToWords: checkpoint1" << endl; //check whether this code works
    }
    else{
      rawWords[i] = ' ';//split into individual keywords through space if there is punctuation.
    }
  }
  string tempString = rawWords; //as rawWord is changed by including space
  stringstream s2(tempString);
  string parsedWord;
  while(s2 >> parsedWord){
    if(2 <= parsedWord.length()){
      converted_rawWord.insert(convToLower(parsedWord));
    }
    else{
      //cout << "parseStringToWords: checkpoint2" << endl;
    }
  }
  return converted_rawWord;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
