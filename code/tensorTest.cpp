#include <iostream>
#include "tensor.h"

using namespace std;

int main()
{
    Tensor t{vector<int>{300,300,5}};
    
    for(int i=0; i<300; i++) {
        for(int j=0; j<300; j++) {
            for(int k=0; k<5; k++) {
                t[i][j][k]=42;
            }
        }
    }
    
    return 0;
}