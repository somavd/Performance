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