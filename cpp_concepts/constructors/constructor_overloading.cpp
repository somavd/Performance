#include<iostream>
using namespace std;

class Params {
public:
    Params() {
        cout << "Default constructor called" << endl;
    }

    Params(int a) {
        cout << "Parameterized constructor called with one int argument" << endl;
    }
    
    Params(int a, int b) {
        cout << "Parameterized constructor called with two int arguments" << endl;
    }

    Params(float a) {
        cout << "Parameterized constructor called with one float argument" << endl;
    }

    Params(float a, float b) {
        cout << "Parameterized constructor called with two float arguments" << endl;
    }
    
    ~Params() {
        cout << "Destructor called" << endl;
    }
};

int main() {
    Params c1;  // Calls default constructor
    Params c2(10);  // Calls parameterized constructor with one int argument
    Params c3(10.5f);  // Calls parameterized constructor with one float argument
    Params c4(10, 20);  // Calls parameterized constructor with two int arguments
    Params c5(10.5f, 20.5f);  // Calls parameterized constructor with two float arguments
    return 0;
}