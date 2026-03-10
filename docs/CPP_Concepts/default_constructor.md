# Default Constructor Demonstration in C++

This project demonstrates the concept of a **default constructor** in
C++ using a simple `uart` class example.

The program creates objects of the `uart` class with and without
explicitly providing parameters to illustrate how constructors behave
with **default parameters**.

------------------------------------------------------------------------

# What is a Default Constructor?

A **default constructor** is a constructor that can be called **without
passing any arguments** when creating an object.

It initializes an object with **default values**.

In C++, a constructor becomes a default constructor if:

-   It has **no parameters**, or
-   **All parameters have default values**

Example:

``` cpp
ClassName();
```

or

``` cpp
ClassName(int value = 0);
```

In this project, the constructor:

``` cpp
uart(uint32_t baud_rate_ = 9600)
```

acts as a **default constructor** because the parameter has a **default
value (9600)**.

------------------------------------------------------------------------

# Program Explanation

The `uart` class simulates a simple UART configuration.

It contains:

## 1. Constructor

Initializes the UART baud rate.

``` cpp
uart(uint32_t baud_rate_ = 9600) : baud_rate(baud_rate_) {
    cout << "Function " << __func__ << " is called with baud_rate: " << baud_rate_ << endl;
}
```

If no value is passed, the baud rate defaults to **9600**.

------------------------------------------------------------------------

## 2. Destructor

Automatically called when the object goes out of scope.

``` cpp
~uart() {
    cout << "Function " << __func__ << " is called" << endl;
}
```

Used here to print when the object is destroyed.

------------------------------------------------------------------------

## 3. Getter Function

Returns the configured baud rate.

``` cpp
uint32_t get_baud_rate() const {
    return baud_rate;
}
```

------------------------------------------------------------------------

# Code

``` cpp
#include<iostream>
using namespace std;

class uart {
public:
    //Constructor with default parameter
    uart(uint32_t baud_rate_ = 9600) : baud_rate(baud_rate_) {
        cout<<"Function "<<__func__<<" is called with baud_rate: "<<baud_rate_<<endl;
    }

    //Destructor
    ~uart() {
        cout<<"Function "<<__func__<<" is called"<<endl;
    }

    uint32_t get_baud_rate() const {
        return baud_rate;
    }

private:
    uint32_t baud_rate;
};

int main(){
    {
        uart u(115200);
        cout<<"Baud rate: "<<u.get_baud_rate()<<endl;
    }
    
    uart u2;
    cout<<"Baud rate: "<<u2.get_baud_rate()<<endl;
    
    return 0;
}
```

------------------------------------------------------------------------

# Program Flow

## Object 1

``` cpp
uart u(115200);
```

Constructor is called with **explicit baud rate = 115200**.

------------------------------------------------------------------------

## Object 2

``` cpp
uart u2;
```

Constructor is called **without parameters**, so it uses the **default
value 9600**.

------------------------------------------------------------------------

# Key Concepts Demonstrated

-   Constructor with **default parameters**
-   **Default constructor behavior**
-   **Destructor invocation**
-   **Scope-based object destruction**
-   Using `__func__` to print the function name
-   Member initialization list

------------------------------------------------------------------------

# Expected Output

    Function uart is called with baud_rate: 115200
    Baud rate: 115200
    Function ~uart is called
    Function uart is called with baud_rate: 9600
    Baud rate: 9600
    Function ~uart is called

------------------------------------------------------------------------

# Build and Run

## Compile

``` bash
g++ main.cpp -o uart_demo
```

## Run

``` bash
./uart_demo
```

------------------------------------------------------------------------

# License

This project is intended for **learning and educational purposes**.
