#include<iostream>
using namespace std;

class uart {
public:
    //Parameterized constructor
    uart(uint32_t baud_rate_) : baud_rate(baud_rate_) {
        cout<<"Function "<<__func__<<" is called with baud_rate: "<<baud_rate_<<endl;
    }

    uart() = default;

    ~uart() {
        cout<<"Function "<<__func__<<" is called"<<endl;
    }

    uint32_t get_baud_rate() const {
        return baud_rate;
    }

private:
    uint32_t baud_rate;
};

int main() {
    uart u(115200);  //Parameterized constructor
    cout<<"Baud rate: "<<u.get_baud_rate()<<endl;
    uart u1;  //Default constructor
    cout<<"Baud rate: "<<u1.get_baud_rate()<<endl;
    return 0;
}