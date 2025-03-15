// Copy in bigint.h (overwrite this file)
#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <vector>

class BigInt {
public:
    BigInt(std::string s, int base=10); // convert string to BigInt
    std::string to_string() const; // get string representation
    void add(BigInt b); // add another BigInt to this one
    void minus(BigInt b); // minus another BigInt to this one
    void removeLeadingZeroes();
    // returns the sum of this BigInt and rhs
    BigInt operator+(const BigInt& rhs) const; 
    // returns the difference of this BigInt minus rhs
    BigInt operator-(const BigInt& rhs) const; 
    // returns the true if this BigInt is less than rhs
    bool operator<(const BigInt& rhs) const; 
private:
    int ubase;
    std::vector<int> v1;
};

#endif