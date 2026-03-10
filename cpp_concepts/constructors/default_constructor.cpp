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