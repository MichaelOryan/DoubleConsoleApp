#ifndef BIGNUMBERS_H
#define BIGNUMBERS_H

class bignumber {
    public:
    bignumber& operator=(const bignumber & rhs);
    bignumber& operator+(const bignumber & rhs);
    bignumber& operator-(const bignumber & rhs);
    bignumber& operator/(const bignumber & rhs);
    bignumber& operator*(const bignumber & rhs);
    bignumber& operator++();
    bignumber operator++(int);
    bignumber& operator--();
    bignumber operator--(int);

    // friend functions for iostreams need to go somewhere

    private:
    typedef int Digit;
    typedef bool Sign;
    vector<Digit> integers;
    vector<Digit> fractions;
    Sign sign;
}

#endif
