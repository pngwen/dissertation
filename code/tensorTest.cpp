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


int main()
{
    Tensor t{TensorDimension{3,3,3}};
    Tensor one{TensorDimension{3,3,3}};
    
    for(int i=0; i<3; i++) {
        for (int j= 0; j<3; j++) {
            for(int k=0; k<3; k++) {
                one[i][j][k] = 1;
            }
        }
    }
    
    t = one * 3; 
    printTensor3(t);
    
    cout << t.norm() << endl;
    
    return 0;
}