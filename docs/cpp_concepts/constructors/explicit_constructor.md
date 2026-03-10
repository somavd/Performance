# C++ Explicit Constructor Demonstration

This example demonstrates the use of the **`explicit` keyword** in C++
constructors and how it prevents **implicit type conversions**.

The program uses a simple `uart_explicit` class representing a UART
configuration with a given baud rate.

------------------------------------------------------------------------

# Source File

**Filename:** `explicit_constructor.cpp`

``` cpp
#include<iostream>
using namespace std;

class uart_explicit {
public:
    explicit uart_explicit(uint32_t baud_rate_) : baud_rate(baud_rate_) {
        cout<<"Function "<<__func__<<" is called with baud_rate: "<<baud_rate_<<endl;
    }

    ~uart_explicit() {
        cout<<"Function "<<__func__<<" is called"<<endl;
    }

    uint32_t get_baud_rate() const {
        return baud_rate;
    }

private:
    uint32_t baud_rate;
};

void uart_explicit_consumer(uart_explicit u) {
    cout<<"Function "<<__func__<<" is called with baud_rate: "<<u.get_baud_rate()<<endl;
}

int main() {
    uart_explicit u(115200);
    uart_explicit_consumer(u);

    //If you uncomment below line, compilation fails as explicit constructor prevents implicit conversion
    //uart_explicit_consumer(12345);
    return 0;
}
```

------------------------------------------------------------------------

# What is an Explicit Constructor?

In C++, the `explicit` keyword is used with constructors to **prevent
implicit type conversions**.

Without `explicit`, the compiler may automatically convert compatible
types using the constructor.

Example without explicit:

``` cpp
uart_consumer(12345);
```

The compiler automatically converts this to:

``` cpp
uart_consumer(uart(12345));
```

This is called **implicit conversion**.

------------------------------------------------------------------------

# Why Use Explicit?

Implicit conversions can sometimes cause **unexpected behavior or
bugs**.

Using `explicit` ensures that objects are created **intentionally and
clearly**.

Example with explicit constructor:

``` cpp
explicit uart_explicit(uint32_t baud_rate_);
```

Now the following is **NOT allowed**:

``` cpp
uart_explicit_consumer(12345);  // Compilation error
```

Instead, you must write:

``` cpp
uart_explicit_consumer(uart_explicit(12345));
```

------------------------------------------------------------------------

# Program Behavior

### Step 1

Object creation:

``` cpp
uart_explicit u(115200);
```

Constructor is called with baud rate **115200**.

------------------------------------------------------------------------

### Step 2

Passing object to function:

``` cpp
uart_explicit_consumer(u);
```

The object is **copied into the function parameter**.

------------------------------------------------------------------------

### Step 3

Destructor Calls

Destructors are invoked when:

-   Function parameters go out of scope
-   Objects leave their scope

------------------------------------------------------------------------

# Expected Output

    Function uart_explicit is called with baud_rate: 115200
    Function uart_explicit_consumer is called with baud_rate: 115200
    Function ~uart_explicit is called
    Function ~uart_explicit is called

------------------------------------------------------------------------

# How to Compile

``` bash
g++ explicit_constructor.cpp -o explicit_constructor
```

------------------------------------------------------------------------

# How to Run

``` bash
./explicit_constructor
```

------------------------------------------------------------------------

# Key Learning Points

This example demonstrates:

-   The purpose of the **`explicit` keyword**
-   Prevention of **implicit constructor conversions**
-   Constructor and destructor invocation
-   Passing objects **by value**
-   Object lifecycle in C++

------------------------------------------------------------------------

# When to Use `explicit`

Use `explicit` for **single‑argument constructors** when you want to
avoid unintended conversions.

Most modern C++ codebases follow the rule:

> If a constructor has a single parameter, it should usually be marked
> `explicit`.

------------------------------------------------------------------------

# License

Educational example for learning **C++ object construction behavior**.
