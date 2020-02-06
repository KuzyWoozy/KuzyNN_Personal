#pragma once

int userInput();

class Fraction final {
    int sub;
    int dom;
    public:
        Fraction(int, int);
        void print() const;
};
