#include <iostream>
#include "tensor.h"

using namespace std;

int main()
{
    Tensor t{TensorDimension{3,3,5}};
    
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            for(int k=0; k<5; k++) {
                //t[i][j][k]=42;
                cout << t[i][j][k] << endl;
            }
        }
    }
    
    cout << t[0][0][100] << endl;
    
    return 0;
}