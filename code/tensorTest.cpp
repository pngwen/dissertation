#include <iostream>
#include "tensor.h"

using namespace std;

void printTensor3(Tensor &t) {
    TensorDimension d = t.dim();
    
    for(int i=0; i<d[0]; i++) {
        for(int j=0; j<d[1]; j++) {
            for(int k=0; k<d[2]; k++) {
                cout << t[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void printTensor2(Tensor &t) {
    TensorDimension d = t.dim();
    
    for(int i=0; i<d[0]; i++) {
        for(int j=0; j<d[1]; j++) {
            cout << t[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    Tensor t1{{3}};
    Tensor t2{{2}};
    

    t1[0]=1;
    t1[1]=2;
    t1[2]=3;

    t2[0]=4;
    t2[1]=5;

    Tensor t3=t1*t2*t1;
    printTensor3(t3);

    return 0;
}

