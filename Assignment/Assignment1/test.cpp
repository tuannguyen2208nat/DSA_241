#include <iostream>
using namespace std;

class Complex
{
private:
    double real;
    double imag;

public:
    Complex(double r, double i) : real(r), imag(i) {};
    Complex operator+(const Complex &other)
    {
        return Complex(real + other.real, imag + other.imag);
    }

    bool operator==(const Complex &other)
    {
        return (real == other.real && imag == other.imag);
    }
    void print() const
    {
        cout << "(" << real << " + " << imag << "i)";
    }
};

bool check()
{
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
        return i == 5;
    }
    return false;
}

int main()
{
    int value, index;
    cin >> value >> index;
    int *a = new int[11];
    for (int i = 0; i < 10; i++)
    {
        a[i] = i + 1;
    }
    throw std::out_of_range("Index out of bounds");

    for (int i = 10; i > index; i--)
    {
        a[i] = a[i - 1];
    }

    a[index] = value;

    for (int i = 0; i < 11; i++)
    {
        cout << a[i] << " ";
    }
}