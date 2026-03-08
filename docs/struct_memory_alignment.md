# Structure Padding and Memory Alignment in C++

This example demonstrates how **structure padding and memory alignment**
affect the size of a struct in C++.

## Source Code

``` cpp
#include<iostream>

using namespace std;

struct node { 
    int a;
    char b;
    int c;
    char d;
};

struct node_opt {
    int a;
    int b;
    char c;
    char d;
};

int main(){
    cout<<"node size: "<<sizeof(node)<<endl;
    cout<<"node_opt size: "<<sizeof(node_opt)<<endl;
    return 0;
}
```

## Program Output

    node size: 16
    node_opt size: 12

------------------------------------------------------------------------

# Why Does This Happen?

Modern CPUs require data to be **aligned in memory** for efficient
access. Because of this, compilers insert **padding bytes** between
structure members.

## Structure 1

``` cpp
struct node { 
    int a;
    char b;
    int c;
    char d;
};
```

Typical sizes:

-   `int` → 4 bytes\
-   `char` → 1 byte

Memory layout:

  Field     Size   Notes
  --------- ------ ---------------------
  int a     4      
  char b    1      
  padding   3      Added for alignment
  int c     4      
  char d    1      
  padding   3      Added for alignment

Total size:

    4 + 1 + 3 + 4 + 1 + 3 = 16 bytes

------------------------------------------------------------------------

## Structure 2 (Optimized)

``` cpp
struct node_opt {
    int a;
    int b;
    char c;
    char d;
};
```

Memory layout:

  Field     Size
  --------- ------
  int a     4
  int b     4
  char c    1
  char d    1
  padding   2

Total size:

    4 + 4 + 1 + 1 + 2 = 12 bytes

------------------------------------------------------------------------

# Key Insight

By simply **reordering structure members**, we reduced memory usage:

    16 bytes → 12 bytes

This is a **25% reduction in memory usage per object**.

When dealing with **millions of objects**, this can significantly
improve:

-   Cache utilization
-   Memory bandwidth
-   Overall system performance

------------------------------------------------------------------------

# Important Takeaway

Before optimizing algorithms, it is often useful to examine **data
structures and memory layout**. Small changes in structure design can
lead to meaningful performance improvements in low-level systems.

------------------------------------------------------------------------

# Source Code

GitHub Repository:\
https://github.com/somavd/Performance/tree/main/codes
