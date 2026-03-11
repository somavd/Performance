This README documents a simple C++ program demonstrating fundamental object-oriented programming concepts, focusing on class constructors, destructors, object lifetime, and function parameter passing mechanisms.

---

# C++ Object Lifecycle and Constructor/Destructor Behavior

This repository contains a C++ example that illustrates how objects are constructed, destructed, and managed within different scopes and function calls. It specifically highlights the behavior of default parameters in constructors, the role of destructors, and the impact of pass-by-value on object lifetime.

## Concept Name

**C++ Class Basics: Constructor, Destructor, Object Lifetime, and Pass-by-Value Semantics**

## Explanation

This C++ code defines a `uart` class, simulating a Universal Asynchronous Receiver-Transmitter (UART) device, primarily to demonstrate core C++ object-oriented features:

1.  **Constructors:** A `uart` object can be initialized with a specific `baud_rate`. The constructor includes a **default parameter** (9600), allowing objects to be created without explicitly providing a baud rate.
2.  **Destructors:** The `~uart()` destructor is defined to log when an object is being destroyed, which helps in tracing the **object's lifetime**.
3.  **Member Initializer List:** The constructor uses a member initializer list (`: baud_rate(baud_rate_)`) for efficient member initialization.
4.  **`const` Member Function:** `get_baud_rate()` is marked `const`, indicating that it does not modify the object's state.
5.  **Object Lifetime and Scope:** The `main` function showcases how objects are created and destroyed based on their scope (e.g., within an inner block `{}`).
6.  **Pass-by-Value Semantics:** The `uart_consumer` function takes a `uart` object **by value**. This is a crucial aspect demonstrated here, as passing by value creates a *copy* of the object, which in turn triggers its own constructor (the copy constructor, implicitly generated in this case) and destructor calls.
7.  **Implicit Conversion:** The code also demonstrates how an integer value can implicitly construct a `uart` object when passed to a function expecting a `uart` object (like `uart_consumer(12345)`).

The verbose `cout` statements using `__func__` are intentionally placed to provide a clear trace of when constructors, destructors, and other functions are invoked.

## Code Walkthrough

Let's trace the execution of the `main` function step by step:

1.  **`int main(){`**
    *   The program execution begins.

2.  **`{ uart u(115200); ... }`**
    *   An inner scope is entered.
    *   `uart u(115200);`: A `uart` object named `u` is created.
        *   The constructor `uart::uart(uint32_t baud_rate_)` is called with `baud_rate_ = 115200`.
        *   Output: `Function uart is called with baud_rate: 115200`
    *   `cout<<"Function "<<__func__<<" is called with baud_rate: "<<u.get_baud_rate()<<endl;`: The `main` function prints the baud rate of `u`.
        *   Output: `Function main is called with baud_rate: 115200`
    *   **`}`**: The inner scope ends.
        *   The object `u` goes out of scope and its destructor is automatically called.
        *   Output: `Function ~uart is called`

3.  **`uart u2;`**
    *   A `uart` object named `u2` is created.
    *   Since no baud rate is provided, the constructor `uart::uart(uint32_t baud_rate_ = 9600)` is called with its default parameter `baud_rate_ = 9600`.
    *   Output: `Function uart is called with baud_rate: 9600`

4.  **`cout<<"Function "<<__func__<<" is called with baud_rate: "<<u2.get_baud_rate()<<endl;`**
    *   The `main` function prints the baud rate of `u2`.
    *   Output: `Function main is called with baud_rate: 9600`

5.  **`uart_consumer(u2);`**
    *   The `uart_consumer` function is called.
    *   Since `u2` is passed **by value**, a *copy* of `u2` is created (let's call it `u_copy`) for the `u` parameter of `uart_consumer`. This involves an implicit copy constructor call.
    *   `uart_consumer` is entered.
    *   Output: `Function uart_consumer is called with baud_rate: 9600`
    *   `uart_consumer` finishes. The `u_copy` object (the parameter `u` within `uart_consumer`) goes out of scope and its destructor is called.
    *   Output: `Function ~uart is called`

6.  **`uart_consumer(12345);`**
    *   The `uart_consumer` function is called with an integer `12345`.
    *   Due to **implicit conversion**, a *temporary `uart` object* is first created using `uart(12345)`.
        *   Output: `Function uart is called with baud_rate: 12345` (This is for the temporary object)
    *   This temporary `uart` object is then passed **by value** to `uart_consumer`, meaning another *copy* is made (let's call it `u_copy_temp`) for the `u` parameter inside `uart_consumer`.
    *   `uart_consumer` is entered.
    *   Output: `Function uart_consumer is called with baud_rate: 12345`
    *   `uart_consumer` finishes. The `u_copy_temp` object (the parameter `u` within `uart_consumer`) goes out of scope and its destructor is called.
    *   Output: `Function ~uart is called`
    *   Immediately after `uart_consumer` returns, the *original temporary `uart` object* (created from `12345`) also goes out of scope and its destructor is called.
    *   Output: `Function ~uart is called`

7.  **`return 0;`**
    *   The `main` function is about to finish.
    *   The `u2` object, which was created in `main`'s scope, goes out of scope and its destructor is called.
    *   Output: `Function ~uart is called`
    *   The program exits.

## Key Learnings

*   **Constructor Invocation:** Constructors are automatically called when an object is created.
    *   Default parameters in constructors allow for flexible object initialization.
    *   Member initializer lists are the preferred way to initialize member variables.
*   **Destructor Invocation:** Destructors are automatically called when an object goes out of scope, ensuring proper cleanup.
*   **Object Lifetime:** The lifetime of an object is tied to its scope. Objects created within an inner block are destroyed when that block ends. Objects created in `main` are destroyed when `main` finishes.
*   **Pass-by-Value:** Passing objects to functions by value creates a *copy* of the object. This involves:
    *   An implicit **copy constructor** call to create the copy.
    *   A destructor call for the copy when the function exits.
    *   This can lead to performance overhead for large objects and unintended side effects if not understood.
*   **Implicit Type Conversion:** C++ allows implicit construction of objects if a suitable constructor exists (e.g., `uart_consumer(12345)` uses `uart(12345)` to create a temporary object). Temporary objects also have a defined lifetime and are destroyed once they are no longer needed (typically at the end of the full expression or statement).
*   **`const` Member Functions:** Marking a member function `const` (`get_baud_rate() const`) ensures that the function does not modify the object's internal state, promoting data integrity and allowing the function to be called on `const` objects.
*   **`__func__` Macro:** A useful predefined macro that expands to the name of the current function, helpful for debugging and logging function calls.

## Example Output

```
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
Function ~uart is called
```