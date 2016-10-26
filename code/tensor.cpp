#include <iostream>
#include <cmath>
#include "tensor.h"

using namespace std;

Tensor::Tensor(const TensorDimension& dims) : d(dims)
{
    //nothing else to init for now!
}


//get the tensor's dimensions
TensorDimension Tensor::dim()
{
    return d;
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


//index operation with tensor index
Tensor::Accessor Tensor::operator[](TensorIndex & i) 
{
    return Accessor(*this, i);
}


//multiply current tensor by a scalar
Tensor & Tensor::operator*=(double rhs)
{
    //mutliply all the non-zero elements
    for(auto itr = elements.begin(); itr != elements.end(); itr++) {
        itr->second *= rhs;
        if(itr->second == 0.0) {
            itr = elements.erase(itr);
        }
    }
    
    return *this;
}
    

//divide current tensor by a scalar
Tensor & Tensor::operator/=(double rhs)
{
    //divide all the non-zero elements
    for(auto itr=elements.begin(); itr != elements.end(); itr++) {
        itr->second /= rhs;
        if(itr->second == 0.0) {
            itr = elements.erase(itr);
        }
    }
    
    return *this;
}
    

//multiply by a scalar and return new tensor
Tensor Tensor::operator*(double rhs)
{
    Tensor nt{*this};
    nt*=rhs;
    
    return nt;
}


//divide by a scalar and return new tensor
Tensor Tensor::operator/(double rhs) 
{
    Tensor nt{*this};
    nt /= rhs;
    
    return nt;
}
    

//add and asign tensor
Tensor & Tensor::operator+=(Tensor &rhs)
{
    if(d != rhs.d) throw out_of_range("Dimension Mismatch");
    
    //go through all the non-zero elements of rhs
    for(auto itr=rhs.elements.begin(); itr!=rhs.elements.end(); itr++) {
        elements[itr->first];
        elements[itr->first] += itr->second;
        if(elements[itr->first] == 0.0) {
            elements.erase(itr->first);
        }
    }
}
    

//subtract and assign tensor
Tensor & Tensor::operator-=(Tensor &rhs)
{
    if(d != rhs.d) throw out_of_range("Dimension Mismatch");
    
    //go through all the non-zero elements of rhs
    for(auto itr=rhs.elements.begin(); itr!=rhs.elements.end(); itr++) {
        elements[itr->first];
        elements[itr->first] -= itr->second;
        if(elements[itr->first] == 0) {
            elements.erase(itr->first);
        }
    }
}
    

//add two tensors and return new tensor
Tensor Tensor::operator+(Tensor &rhs)
{
    Tensor nt{*this};
    nt += rhs;
    return nt;
}
    

//subtract two tensors and return new tensor
Tensor Tensor::operator-(Tensor &rhs)
{
    Tensor nt{*this};
    nt -= rhs;
    return nt;
}
    

//compute the Frobenius Norm of the tensor
double Tensor::norm()
{
    double sum = 0;
    
    //add the square of all the non-zero elements
    for(auto itr=elements.begin(); itr!=elements.end(); itr++) {
        sum += itr->second * itr->second;
    }
    
    return sqrt(sum);
}


//outer tensor product
Tensor Tensor::operator*(Tensor & rhs) 
{
    //first we need to make our dimension
    TensorDimension d(this->d);
    d.append(rhs.d);
    
    //now we make the resultant tensor
    Tensor t(d);
    
    //now we multiply all the non-zero tensor elements of our tensor by
    //all the non-zero elements of the rhs tensor
    for(auto itr=elements.begin(); itr != elements.end(); itr++) {
        for(auto itr2=rhs.elements.begin(); itr2 != rhs.elements.end(); itr2++) {
            TensorIndex i{itr->first};
            i.append(itr2->first);
            t.elements[i] = itr->second * itr2->second;
        }
    }
    
    return t;
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
    t.elements[index] = rhs;

    //keep it sparse
    if(rhs == 0) {
        t.elements.erase(index);
    }

    return rhs;
} 


double Tensor::Accessor::operator+=(double rhs) 
{
    double x;
    
    x = (double) *this;   //get the value (or crash if invalid cast!)
    return t.elements[index] = x + rhs;
}


double Tensor::Accessor::operator-=(double rhs)
{
    double x;
    
    x = (double) *this;   //get the value (or crash if invalid cast!)
    return t.elements[index] = x - rhs;
}


double Tensor::Accessor::operator*=(double rhs)
{
    double x;
    
    x = (double) *this;   //get the value (or crash if invalid cast!)
    return t.elements[index] = x * rhs;
}


double Tensor::Accessor::operator/=(double rhs)
{
    double x;
    
    x = (double) *this;   //get the value (or crash if invalid cast!)
    return t.elements[index] = x / rhs;
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
