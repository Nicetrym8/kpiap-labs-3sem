#include <iostream>
#include <string>

class Complex
{
private:
    float real;
    float imag;

public:
    Complex(float real = 0, float imag = 0) : imag(imag), real(real){};
    friend std::ostream &operator<<(std::ostream &out, const Complex &obj)
    {
        out << obj.real << std::showpos << obj.imag << std::noshowpos << 'i';
        return out;
    }
    friend bool operator==(const Complex &lhs, const Complex &rhs)
    {
        return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
    }
    friend Complex operator+(const Complex &lhs, const Complex &rhs)
    {
        return Complex(lhs.real + rhs.real, lhs.imag + rhs.imag);
    }
    Complex operator-(const Complex &obj)
    {
        return Complex(this->real - obj.real, this->imag - obj.imag);
    }
    bool operator>(const Complex &obj)
    {
        return this->real > obj.real;
    }
    operator int() const { return (int)this->real; };
    operator double() const { return (double)this->real; };
};
int main()
{
    auto a = Complex(1, 6),
         b = Complex(2, -8),
         c = Complex(-7.2, 2.1);
    std::cout << "Complex:" << std::endl
              << a << std::endl
              << b << std::endl
              << c << std::endl
              << "a + b: " << (a + b) << std::endl
              << "a - b: " << (a - b) << std::endl
              << "Cast a to int: " << ((int)a) << std::endl
              << "Cast c to double: " << ((double)c) << std::endl
              << "Compare a & b: " << (a == b) << std::endl
              << "Is a > c: " << (a > c) << std::endl;
}
