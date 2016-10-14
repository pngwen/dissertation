#include <iostream>
#include "tensor.h"

using namespace std;

Tensor::Tensor(vector<int> dims) : d(dims)
{
    //nothing else to init for now!
}


Tensor::~Tensor() 
{
    //delete all of our non-zero elements
    for(auto itr = elements.begin(); itr != elements.end(); itr++) {
        delete itr->second;
    }
    elements.clear();
}


// the index operator.  If the element does not yet, we add it to the list
TensorBase & Tensor::operator[](int i) 
{
    //bounds check!
    if(i >= d[0]) throw out_of_range("Index out of bounds");
    
    if(elements.find(i) == elements.end()) {
        //ok, so we have to set up our tensor!
        TensorBase *t;

        //create the asked for tensor
        if(d.size()==1) {
            //tensor row
            t = new TensorScalar();
        } else {
            //tensor with one fewer dimension
            t = new Tensor(vector<int>(d.begin()+1, d.end()));
        }
        
        //put it in the elements list
        elements[i] = t;
    }
    
    return *(elements[i]);
}