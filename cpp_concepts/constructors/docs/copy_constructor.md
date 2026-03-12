Here's a GitHub-style README for the provided C++ code.

---

# Dynamic Array with Custom Copy Constructor (Deep Copy)

This repository contains a simple C++ program demonstrating how to implement a dynamic array class with proper resource management, specifically focusing on the implementation of a **custom copy constructor** to perform a **deep copy**.

## Concept Name

**Deep Copy Semantics for Classes Managing Dynamic Memory**

## Explanation

This C++ code illustrates the implementation of a basic `DynamicArray` class that manages an array of integers on the heap. The primary purpose is to highlight proper resource management when a class owns dynamically allocated memory.

When a class holds raw pointers to dynamically allocated resources (like `int* arr` in this example), the default copy constructor provided by the compiler performs a **shallow copy**. A shallow copy simply copies the pointer address, meaning both the original and the copied object end up pointing to the *same* underlying memory. This can lead to serious issues such as:

*   **Double-Free Errors:** When both objects are destroyed, their destructors attempt to deallocate the same memory block twice.
*   **Dangling Pointers:** If one object deallocates the shared memory, the other object's pointer becomes invalid, leading to undefined behavior if accessed.

To prevent these problems, a **deep copy** is required. A deep copy involves allocating new memory for the copied object and then copying the *contents* of the original object's data into this new memory. This ensures that each object has its own independent copy of the resources. This example showcases how to achieve this using a custom copy constructor.

## Code Walkthrough

Let's break down the key components of the `DynamicArray` class and the `main` function.

### `DynamicArray` Class

This class encapsulates a dynamically allocated array of integers.

*   **`private` Members:**
    *   `uint32_t size;`: Stores the current size of the dynamic array.
    *   `int* arr;`: A pointer to the actual array of integers allocated on the heap.

*   **`DynamicArray(uint32_t size_)` (Default Constructor):**
    ```cpp
    DynamicArray(uint32_t size_) : size(size_) {
        arr = new int[size];
    }
    ```
    *   This constructor is responsible for initializing a new `DynamicArray` object.
    *   It takes an `uint32_t size_` argument, which determines the capacity of the array.
    *   It uses an initializer list (`: size(size_)`) to set the `size` member.
    *   Crucially, it allocates a new array of `int`s on the heap using `new int[size]` and stores the pointer to this memory in the `arr` member.

*   **`DynamicArray(const DynamicArray& other)` (Copy Constructor):**
    ```cpp
    DynamicArray(const DynamicArray& other) : size(other.size) {
        arr = new int[size];
        for(uint32_t i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        cout << "Copy constructor called" << endl;
    }
    ```
    *   This is the core of the deep copy implementation. It takes a constant reference `other` to another `DynamicArray` object as its argument.
    *   It initializes the `size` of the new object to be the same as `other.size`.
    *   **Deep Copy Step 1:** It allocates *new* memory on the heap for the `arr` pointer of the current object using `new int[size]`. This is vital; without this, it would be a shallow copy.
    *   **Deep Copy Step 2:** It then iterates through the elements of `other.arr` and copies each element's *value* into the newly allocated `arr` of the current object.
    *   A `cout` statement is included to explicitly demonstrate when this constructor is invoked.

*   **`uint32_t getSize() const` (Getter Method):**
    ```cpp
    uint32_t getSize() const {
        return size;
    }
    ```
    *   A simple `const` method to return the `size` of the dynamic array. The `const` keyword indicates that this method does not modify the object's state.

*   **`~DynamicArray()` (Destructor):**
    ```cpp
    ~DynamicArray() {
        delete[] arr;
    }
    ```
    *   This special member function is automatically called when a `DynamicArray` object goes out of scope or is explicitly deleted.
    *   Its responsibility is to deallocate the memory pointed to by `arr` using `delete[] arr;` to prevent memory leaks. The `[]` operator is essential when deallocating arrays.

### `main()` Function

```cpp
int main() {
    DynamicArray d(5);
    cout<<"Size: "<<d.getSize()<<endl;

    DynamicArray d2 = d; // Copy constructor called
    cout<<"Size: "<<d2.getSize()<<endl;

    return 0;
}
```

*   `DynamicArray d(5);`: An object `d` of `DynamicArray` is created with a size of 5. The default constructor is invoked, allocating memory for 5 integers.
*   `cout<<"Size: "<<d.getSize()<<endl;`: Prints the size of `d`.
*   `DynamicArray d2 = d;`: This is the crucial line that **invokes the custom copy constructor**. A new `DynamicArray` object `d2` is created and initialized using the contents of `d`. Due to the custom implementation, `d2` receives its own, independent copy of the underlying array data (a deep copy).
*   `cout<<"Size: "<<d2.getSize()<<endl;`: Prints the size of `d2`.

## Key Learnings

1.  **Resource Management with Raw Pointers:** When your C++ class directly manages dynamic memory (using `new` and `delete`) via raw pointers, you are responsible for defining special member functions to handle resource allocation, deallocation, and copying.
2.  **Shallow vs. Deep Copy:**
    *   **Shallow Copy:** The default behavior for classes with raw pointers is a member-wise copy, which means only the pointer *address* is copied, leading to both objects pointing to the same memory. This is problematic for resource management.
    *   **Deep Copy:** To ensure each object has its own independent resources, you must explicitly allocate new memory for the copied object and then copy the *contents* from the source.
3.  **The Need for a Custom Copy Constructor:** A custom copy constructor is essential when a class owns resources allocated on the heap (or other managed resources) to correctly implement deep copy semantics and prevent issues like double-free errors and dangling pointers.
4.  **The Rule of Three/Five/Zero:** This fundamental C++ guideline states that if you define any of the following for your class, you probably need to define all of them:
    *   Destructor (`~MyClass()`)
    *   Copy Constructor (`MyClass(const MyClass& other)`)
    *   Copy Assignment Operator (`MyClass& operator=(const MyClass& other)`)
    (C++11 introduced move constructor and move assignment operator, leading to the "Rule of Five". The "Rule of Zero" suggests avoiding raw resource management altogether by using smart pointers like `std::unique_ptr` and `std::shared_ptr` to automate resource management and leverage RAII.)
5.  **Destructor's Role:** The destructor (`~DynamicArray()`) is vital for releasing dynamically allocated memory using `delete[]` to prevent memory leaks.

## Example Output

When you compile and run the provided C++ code, you will see the following output:

```
Size: 5
Copy constructor called
Size: 5
```