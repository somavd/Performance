#include<iostream>
using namespace std;

class DynamicArray {
public:
    //Default Constructor
    DynamicArray(uint32_t size_) : size(size_) {
        arr = new int[size];
    }

    //Copy Constructor
    DynamicArray(const DynamicArray& other) : size(other.size) {
        arr = new int[size];
        for(uint32_t i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        cout << "Copy constructor called" << endl;
    }
    
    uint32_t getSize() const {
        return size;
    }

    ~DynamicArray() {
        delete[] arr;
    }
private:
    uint32_t size;
    int* arr;
};

int main() {
    DynamicArray d(5);
    cout<<"Size: "<<d.getSize()<<endl;
    DynamicArray d2 = d; // Copy constructor called
    cout<<"Size: "<<d2.getSize()<<endl;
    return 0;
}