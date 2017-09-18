#include <iostream>
#include <iomanip>
#include "tensor.h"

using namespace std;

void printTensor(Tensor<> &t)
{
    Tensor<>::Index lidx;  //index for determininig line shifts
    auto itr = t.begin();  //start the iterator

    //capture the initial index for the first line
    lidx = itr.index();

    //display all the tensor elements with some tabbing action
    for(itr; itr != t.end(); itr++) {
        //detect end of line for each index after the first one
        for(int i=1; i<lidx.size(); i++) {
            //each mismatched higher dimension results in an endl
            if(lidx[i] != itr.index()[i]) {
                cout << endl;
            }
        }

        //print the element
        cout << "\t" << *itr;

        //the current index is now our new basis index
        lidx = itr.index();
    }

    //end the last line
    cout << endl;
}


void sparsePrint(Tensor<> &t)
{
    auto d = t.dim();
    cout << "Dimensions: [";
    for(int i=0; i<d.size(); i++) {
        cout << ' ' << d[i];
    }
    cout << " ]" << endl;

    for(auto itr=t.sparseBegin(); itr != t.sparseEnd(); itr++) {
        for(int i=0; i<d.size(); i++) {
            cout << itr.index()[i] << ' ';
        }
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

    //test the prints
    cout << endl << "Print Test" << endl;
    printTensor(a);
    cout << "-----" << endl;
    printTensor(b);
    cout << "-----" << endl;
    c=a.outer(a);
    c=c.outer(a);
    c=c.outer(a);
    cout << c.dim().size() << " Modes ["; 
    for(int i=0; i<c.dim().size(); i++) {
       cout << " " << c.dim()[i];
    }
    cout << "]" << endl;
    printTensor(c);

    //sparse tensor test
    cout << endl << "Sparse Iterator Test" << endl;
    a=Tensor<>{20000,20000,35000};
    a[1][2][0] = 25.0;
    a[1000][200][10000] = 75.0;
    a[19000][19000][1985] = 90.0;
    sparsePrint(a);

    return 0;
}

