#include <iostream>
#include "tensor.h"

using namespace std;

Tensor::Tensor(const TensorDimension& dims) : d(dims)
{
    //nothing else to init for now!
}



//index operation (start of the chain of accessors)
Tensor::Accessor Tensor::operator[](int i)
{
    //check the bounds
    if(i>=d[0]) throw out_of_range("Tensor index out of range.");
    
    //start our index off
    TensorIndex index(d.size());
    index[0] = i;
    
    //return the accessor
    return Accessor(*this, index);
}


//////////////////////////////////////////
// Accessor
/////////////////////////////////////////
Tensor::Accessor Tensor::Accessor::operator[](int i)
{
    int ni;
    
    //find the next ni
    for(ni=0; ni<index.size() and index[ni] != -1; ni++);
    
    //bounds checks
    if(ni == index.size()) throw out_of_range("Too many dimensions specified.");
    if(i >= t.d[ni]) throw out_of_range("Tensor index out of range.");
    
    //build the next accessor
    TensorIndex nextIndex(index);
    nextIndex[ni] = i;
    return Accessor(t, nextIndex);
}


double Tensor::Accessor::operator=(double rhs)
{
    //check for validity of the index
    for(int i=0; i<index.size(); i++) {
        if(index[i] == -1) throw bad_cast();
    }
    
    //make the assignment
    return t.elements[index] = rhs;
} 


Tensor::Accessor::operator double()
{
    //check for validity of the index
    for(int i=0; i<index.size(); i++) {
        if(index[i] == -1) throw bad_cast();
    }
    
    
    //check for an empty element and return 0
    if(t.elements.find(index) == t.elements.end()) {
        return 0;
    }
    
    return t.elements[index];
}