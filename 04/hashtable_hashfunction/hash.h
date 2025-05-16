#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
			// Add your code here
			int exponent = 0;
			HASH_INDEX_T wval = 0;
			std::vector<HASH_INDEX_T> w = {0, 0, 0, 0, 0};
			int widx = 4;
			//letterDigitToNumber
			for(int i = k.size()-1; i >=0; i--){ 
				char letter = tolower(k[i]);
				int base;
				if(('a' <= letter) && (letter <= 'z')){
					base = letter - 'a';
				}
				else if(('0' <= letter) && (letter <= '9')){
					base = letter - '0' + 26;
				}
				else{
					base = 0; 
				}
				wval += base*std::pow(36,exponent);
				exponent++;
				if((exponent%6 == 0) || (i == 0)){
					w[widx] = wval;
					widx--;
					exponent = 0;
					wval = 0;
				}
			}
			unsigned long long hash = 0;
			for(HASH_INDEX_T i = 0; i < w.size(); i++){
				hash += rValues[i] * w[i];
			}
			for(HASH_INDEX_T i = 0; i < w.size(); i++){
				std::cout << "w[" << i << "] = " << w[i] << std::endl;
			}
			return hash;
    }

    // // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    // HASH_INDEX_T letterDigitToNumber(char letter) const
    // {
    //     // Add code here or delete this helper function if you do not want it

    // }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
