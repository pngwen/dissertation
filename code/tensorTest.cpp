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
    Tensor<> t1{2,2};
    Tensor<> t2{2,2};
    Tensor<> t3(t2);
    Tensor<>::Index i(2);
    Tensor<>::Index j(2);
    Tensor<>::Iterator itr;
    
    i[0] = 0;
    i[1] = 1;
    j[0] = 1;
    j[1] = 1;
    cout << (i<j) << endl;
    cout << (j<i) << endl;
    
    cout << "T1" << endl;
    t1[0][0] = 1;
    t1[0][1] = 3;
    t1[1][0] = 2;
    t1[1][1] = 4;
    printTensor(t1);
    
    t2.fill(3);
    cout << "T2" << endl;
    printTensor(t2);
    
    t3 = t1 + t2;
    cout << "T3" << endl;
    printTensor(t3);
    
    
    //accessor tests
    t2.fill(2);
    t2[0][0]*=3;
    t2[1][0]+=2;
    t2[0][1]-=5;
    t2[1][1]/=8;
    cout << "After Accessor Arithmetic Test" << endl;
    printTensor(t2);
  
    //index tests
    i=t2.dim();
    cout << i[0] << ", " << i[1] << endl;
    
    //iterator tests
    i=t2.begin().index();
    cout << i[0] << ", " << i[1] << endl;
    
    itr=t2.begin();
    i=itr.index();
    cout << i[0] << ", " << i[1] << endl;
    
    itr=t2.begin()+3;
    i=itr.index();
    cout << i[0] << ", " << i[1] << endl;
    
    itr=itr-1;
    i=itr.index();
    cout << i[0] << ", " << i[1] << endl;
    
    itr=t2.begin()+7;
    i=itr.index();
    cout << i[0] << ", " << i[1] << endl;
    
    
    //scalar tests
    cout << "Scalar Multiply"<< endl;
    t2.fill(2);
    t2[0][0]=3;
    t3 = t2 * 2;
    printTensor(t3);
    
    cout << "In Place Scalar Multiply" << endl;
    t2.fill(2);
    t2[0][0]=3;
    t2*=2;
    
    cout << "Scalar Divide"<< endl;
    t2.fill(2);
    t2[0][0]=3;
    t3 = t2 / 2;
    printTensor(t3);
    
    cout << "In Place Scalar Divide" << endl;
    t2.fill(2);
    t2[0][0]=3;
    t2/=2;
    printTensor(t2);
    
    cout << "Tensor Add" << endl;
    t1.fill(2);
    t1[0][0]=3;
    t2.fill(1);
    t2[0][0]=2;
    t2[1][0]=3;
    t3=t1+t2;
    printTensor(t3);
    
    cout << "In place Tensor Add" << endl;
    t1.fill(2);
    t1[0][0]=3;
    t2.fill(1);
    t2[0][0]=2;
    t2[1][0]=3;
    t1+=t2;
    printTensor(t1);
    
    cout << "Tensor Subtract" << endl;
    t1.fill(2);
    t1[0][0]=3;
    t2.fill(1);
    t2[0][0]=2;
    t2[1][0]=3;
    t3=t1-t2;
    printTensor(t3);
    
    cout << "In place Tensor Subtract" << endl;
    t1.fill(2);
    t1[0][0]=3;
    t2.fill(1);
    t2[0][0]=2;
    t2[1][0]=3;
    t1-=t2;
    printTensor(t1);
    
    return 0;
}

