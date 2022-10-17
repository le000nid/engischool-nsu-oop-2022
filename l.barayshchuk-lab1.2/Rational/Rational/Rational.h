#ifndef L_BARAYSHCHUK_LAB1_2_RATIONAL_H
#define L_BARAYSHCHUK_LAB1_2_RATIONAL_H


#include <stdexcept>
#include <string>
#include <cmath>

class Rational {

public:
    Rational(int num, int den);
    Rational(int num);
    Rational();

    friend std::ostream& operator<< (std::ostream&, Rational const&);
    friend std::istream& operator>> (std::istream&, Rational&);

    Rational operator+ (Rational &other);
    Rational operator+ (const int& other);

    Rational operator- (Rational &other);
    Rational operator- (const int& other);

    Rational operator* (Rational &other);
    Rational operator* (const int& other);

    Rational operator/ (Rational &other);
    Rational operator/ (const int& other);

    bool operator== (Rational& other);
    bool operator== (const int& other);

    bool operator!= (Rational& other);
    bool operator!= (const int& other);

    bool operator< (Rational& other);
    bool operator< (const int& other);

    bool operator> (Rational& other);
    bool operator> (const int& other);

    bool operator<= (Rational& other);
    bool operator<= (const int& other);

    bool operator>= (Rational& other);
    bool operator>= (const int& other);

private:
    int num, den;

    static int Gcd(int a, int b)
    {
        while (a && b)
            a > b ? a %= b : b %= a;
        return a | b;
    }

    void BringToGcd1(){
        int gcd = Gcd(abs(num), den);
        if(gcd != 1){
            this->num /= gcd;
            this->den /= gcd;
        }
    }
};

Rational::Rational(int num, int den): num(num), den(den) {

    if(den<=0){
        throw std::invalid_argument("denominator should be >0");
    }

    this->BringToGcd1();
}

Rational::Rational(int num): num(num), den(1) {}

Rational::Rational() : num(0), den(1) {}

std::ostream& operator <<(std::ostream& ost, Rational const& r)
{
    return ost << (double)r.num / (double)r.den;
}

std::istream& operator>>(std::istream& ist, Rational& r)
{
    std::cout << "Numerator: ";
    ist >> r.num;
    std::cout << "Denominator: ";
    ist >> r.den;
    r.BringToGcd1();
    return ist;
}

Rational Rational::operator+(Rational &other) {
    Rational result = Rational(this->num * other.den + other.num * this->den, this->den * other.den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator+(const int& other) {
    Rational result = Rational(this->num + other * this->den, this->den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator-(Rational& other) {
    Rational result = Rational(this->num * other.den - other.num * this->den, this->den * other.den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator-(const int& other) {
    Rational result = Rational(this->num - other * this->den, this->den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator*(Rational& other) {
    Rational result = Rational(this->num * other.num, this->den * other.den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator*(const int& other) {
    Rational result = Rational(this->num * other, this->den);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator/(Rational& other) {
    Rational result = Rational(this->num * other.den, this->den * other.num);
    result.BringToGcd1();
    return result;
}

Rational Rational::operator/(const int& other) {
    Rational result = Rational(this->num, this->den * other);
    result.BringToGcd1();
    return result;
}

bool Rational::operator== (Rational& other)
{
    return (this->num == other.num && this->den == other.den);
}

bool Rational::operator== (const int& other)
{
    return (this->num == other && this->den == 1);
}

bool Rational::operator!= (Rational& other)
{
    return (this->num != other.num);
}

bool Rational::operator!= (const int& other)
{
    return !(this->num == other && this->den == 1);
}

bool Rational::operator< (Rational& other)
{
    return (this->num * other.den < other.num * this->den);
}

bool Rational::operator< (const int& other)
{
    return !(this->num < other * this->den);
}

bool Rational::operator> (Rational& other)
{
    return (this->num * other.den > other.num* this->den);
}

bool Rational::operator> (const int& other)
{
    return !(this->num > other* this->den);
}

bool Rational::operator<= (Rational& other)
{
    return (this->num * other.den <= other.num * this->den);
}

bool Rational::operator<= (const int& other)
{
    return !(this->num <= other * this->den);
}

bool Rational::operator>= (Rational& other)
{
    return (this->num * other.den >= other.num * this->den);
}

bool Rational::operator>= (const int& other)
{
    return !(this->num >= other * this->den);
}

#endif //L_BARAYSHCHUK_LAB1_2_RATIONAL_H
