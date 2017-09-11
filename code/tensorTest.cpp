#include <iostream>
#include <iomanip>
#include "tensor.h"

using namespace std;

void printTensor(Tensor<> &t)
{
    Tensor<>::Index d = t.dim();
    for(auto k = 0; k<d[2]; k++) {
        for(auto i = 0; i<d[0]; i++) {
            for(auto j = 0; j<d[1]; j++) {
                cout << setw(5) << t[i][j][k]; 
            }
            cout << endl;  //new row
        }
        cout << endl; //blank line
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


    //test the outer product
    a = Tensor<>{2};
    a[0] = 1;
    a[1] = 2;
    b = Tensor<>{2};
    b[0] = 3;
    b[1] = 4;
    c = a.outer(b);
    c = c.outer(a);
    cout << endl << "Outer Product: [1 2] o [3 4] o [1 2]"<<endl;
    printTensor(c);

    cout << endl << "Outer Product: [1 2] o [3 4] o [0]"<<endl;
    a = Tensor<>{2};
    a[0] = 1;
    a[1] = 2;
    b = Tensor<>{2};
    b[0] = 3;
    b[1] = 4;
    c = a.outer(b);
    b = Tensor<>{1};
    b[0] = 0;
    c = c.outer(b);
    printTensor(c);

    return 0;
}

