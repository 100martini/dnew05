// #ifndef BIGINT_HPP
// #define BIGINT_HPP

// #include <iostream>
// #include <string>
// #include <algorithm>

// class bigint {
// private:
//     std::string digits;
//     static std::string addStrings(const std::string& a, const std::string& b);
//     void removeLeadingZeros();

// public:
//     bigint();
//     bigint(unsigned int num);
//     bigint(const std::string& str);

//     // Addition
//     bigint operator+(const bigint& other) const;
//     bigint& operator+=(const bigint& other);

//     // Comparison
//     bool operator==(const bigint& other) const;
//     bool operator!=(const bigint& other) const;
//     bool operator<(const bigint& other) const;
//     bool operator>(const bigint& other) const;
//     bool operator<=(const bigint& other) const;
//     bool operator>=(const bigint& other) const;

//     // Digit shift (base 10)
//     bigint operator<<(unsigned int shift) const;
//     bigint operator>>(unsigned int shift) const;
//     bigint& operator<<=(unsigned int shift);
//     bigint& operator>>=(unsigned int shift);

//     // Special operators:
//     bigint operator++(int); // Post-increment x++
//     bigint& operator++();   // Pre-increment ++x
//     // bigint operator<<+(unsigned int shift) const; // shift left then add
//     // bigint operator>>+(unsigned int shift) const; // shift right then add

//     // For stream output
//     std::string getDigits() const;
//     bool isZero() const { return digits.size() == 1 && digits[0] == '0'; }
// };
// std::ostream& operator<<(std::ostream& os, const bigint& num);

// #endif // BIGINT_HPP

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint {
private:
    std::string digits;
    std::string addStrings(const std::string& a, const std::string& b) const;
    void removeLeadingZeros();
    bool isZero() const;
    
public:
    bigint();
    bigint(unsigned int num);
    bigint(const std::string& str);
    
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);
    
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;
    
    bigint operator<<(unsigned int shift) const;
    bigint operator>>(unsigned int shift) const;
    bigint& operator<<=(unsigned int shift);
    bigint& operator>>=(unsigned int shift);
    
    bigint& operator++();     
    bigint operator++(int);    
    
    std::string getDigits() const;
};
std::ostream& operator<<(std::ostream& os, const bigint& num);

#endif