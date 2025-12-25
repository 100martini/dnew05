#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
        int data[2];
    public:
        vect2(int x = 0, int y = 0);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);
        
        int& operator[](int index);
        const int& operator[](int index)const;

        vect2 operator+(const vect2& other)const;
        vect2 operator-(const vect2& other)const;
        vect2 operator*(int carry)const;
        vect2 operator-();
        vect2 operator+();
        
        vect2& operator+=(const vect2& other);
        vect2& operator-=(const vect2& other);
        vect2& operator*=(int carry);
        
        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);
        
        bool operator==(const vect2& other)const;
        bool operator!=(const vect2& other)const;
};
vect2 operator*(int carry, const vect2& v);
std::ostream& operator<<(std::ostream& s, const vect2& v);

#endif