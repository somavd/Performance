# C++ Default Constructor Demonstration (UART Example)

This project demonstrates how **default constructors**, **default
parameters**, and **implicit object construction** work in C++ using a
simple `uart` class.

It also illustrates:

-   Constructor calls
-   Destructor calls
-   Passing objects **by value**
-   **Implicit type conversion** using constructors
-   Object lifetime and scope behavior

------------------------------------------------------------------------

# Source Code

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

void uart_consumer(uart u) {
    cout<<"Function "<<__func__<<" is called with baud_rate: "<<u.get_baud_rate()<<endl;
}

int main(){
    {
        uart u(115200);
        cout<<"Function "<<__func__<<" is called with baud_rate: "<<u.get_baud_rate()<<endl;
    }
    
    uart u2;
    cout<<"Function "<<__func__<<" is called with baud_rate: "<<u2.get_baud_rate()<<endl;
    
    uart_consumer(u2);
    uart_consumer(12345);
    
    return 0;
}
```

------------------------------------------------------------------------

# What is a Default Constructor?

A **default constructor** is a constructor that can be called **without
any arguments**.

In C++, a constructor is considered a default constructor if:

-   It has **no parameters**, OR
-   **All parameters have default values**

Example:

``` cpp
uart(uint32_t baud_rate_ = 9600);
```

This allows both:

``` cpp
uart u;        // uses default value
uart u(115200); // custom value
```

------------------------------------------------------------------------

# Key Concepts Demonstrated

## 1. Constructor with Default Parameter

``` cpp
uart(uint32_t baud_rate_ = 9600)
```

If no argument is provided, the constructor automatically uses **9600**
as the baud rate.

Example:

``` cpp
uart u2;
```

Result:

    Function uart is called with baud_rate: 9600

------------------------------------------------------------------------

# 2. Member Initialization List

The constructor initializes class members using an **initialization
list**:

``` cpp
: baud_rate(baud_rate_)
```

This is the recommended way to initialize member variables.

------------------------------------------------------------------------

# 3. Destructor Behavior

``` cpp
~uart()
```

The destructor runs automatically when the object goes **out of scope**.

Example:

``` cpp
{
    uart u(115200);
}
```

When the block ends, the destructor is called.

------------------------------------------------------------------------

# 4. Passing Objects by Value

Function:

``` cpp
void uart_consumer(uart u)
```

The object is **copied** when passed to the function.

``` cpp
uart_consumer(u2);
```

A temporary copy of `u2` is created.

------------------------------------------------------------------------

# 5. Implicit Conversion using Constructor

This line:

``` cpp
uart_consumer(12345);
```

works because the constructor accepts an integer parameter.

The compiler performs:

``` cpp
uart_consumer(uart(12345));
```

So a temporary `uart` object is created with baud rate **12345**.

------------------------------------------------------------------------

# Program Flow

### Step 1

    uart u(115200);

Output:

    Function uart is called with baud_rate: 115200
    Function main is called with baud_rate: 115200

Destructor called when block ends.

------------------------------------------------------------------------

### Step 2

    uart u2;

Uses default value:

    Function uart is called with baud_rate: 9600

------------------------------------------------------------------------

### Step 3

    uart_consumer(u2);

A copy of `u2` is passed.

------------------------------------------------------------------------

### Step 4

    uart_consumer(12345);

Implicit constructor call creates temporary object.

------------------------------------------------------------------------

# Expected Output (Approximate)

    Function uart is called with baud_rate: 115200
    Function main is called with baud_rate: 115200
    Function ~uart is called

    Function uart is called with baud_rate: 9600
    Function main is called with baud_rate: 9600

    Function uart_consumer is called with baud_rate: 9600
    Function ~uart is called

    Function uart is called with baud_rate: 12345
    Function uart_consumer is called with baud_rate: 12345
    Function ~uart is called
    Function ~uart is called

------------------------------------------------------------------------

# How to Compile

``` bash
g++ default_constructor.cpp -o uart_demo
```

------------------------------------------------------------------------

# How to Run

``` bash
./uart_demo
```

------------------------------------------------------------------------

# Learning Outcomes

After studying this example you should understand:

-   Default constructors
-   Default parameters
-   Constructor initialization lists
-   Destructor invocation
-   Temporary objects
-   Implicit constructor conversions
-   Passing objects by value

------------------------------------------------------------------------

# License

This project is for **educational and demonstration purposes**.
