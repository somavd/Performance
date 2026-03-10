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
