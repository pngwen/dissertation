#include <iostream>
#include "tensor.h"

using namespace std;

void printTensor(Tensor<> &t)
{
    for(auto itr=t.begin(); itr != t.end(); itr++) {
        cout << *itr << endl;
    }
}

int main()
{
    Tensor<> a{2,2,2};
    Tensor<> b{2,2,2};
    Tensor<> c{2,2,2};

    //initialize a and b
    a[0][0][0]  = 1;
    a[1][1][1]  = 1;
    b[0][1][0]  = 2;
    b[1][1][1]  = 2;


    //print a and b
    cout << "A" << endl;
    printTensor(a);
    cout << endl << "B" << endl; 
    printTensor(b);
    cout << endl << "A+B" << endl;
    c = a+b;
    printTensor(c);
    c = a;
    c+=b;
    cout << endl << "C=8; C+=b" << endl;
    printTensor(c);
    cout << endl << "A-B" << endl;
    c = a-b;
    printTensor(c);
    c = a;
    c-=b;
    cout << endl << "C=a; C-=b" << endl;
    printTensor(c);

    c = a * 4;
    cout << endl << "A * 4" << endl;
    printTensor(c);


    cout << endl << "C=A; C*=4" << endl;
    c = a;
    c *= 4;

    c = a / 4;
    cout << endl << "A / 4" << endl;
    printTensor(c);


    cout << endl << "C=A; C/=4" << endl;
    c = a;
    c /= 4;
    printTensor(c);

    return 0;
}

