/*
 * File: tensor.h
 * Purpose: Declaration of a tensor class.  
 * Author: Robert Lowe
 */
#ifndef TENSOR_H
#define TENSOR_H
#include <map>
#include <vector>
#include <exception>
#include <typeinfo>
#include <initializer_list>


//serves as an index into a tensor
class TensorIndex
{
public:
    //create the index from an initializer list
    TensorIndex(std::initializer_list<int>l) : v(l.begin(), l.end()) { /* just capture the list */ }
    
    //create an index for an n-dimensioned tensor (initialized to -1)
    TensorIndex(int n) : v(n, -1) { /* all done! */ }
    
    //copy constructor
    TensorIndex(const TensorIndex &rhs) : v(rhs.v.begin(), rhs.v.end()) { /* nothing */ }
    
    //provides access to the index element
    int & operator[](int i) { return v[i]; }
    
    //returns the number of dimensions
    int size() const { return v.size(); }
    
    //comparison operations
    bool operator<(const TensorIndex& rhs) const { return compare(rhs) < 0; }
    bool operator==(const TensorIndex& rhs) const { return compare(rhs) == 0; }
    bool operator!=(const TensorIndex& rhs) const { return compare(rhs) != 0; }
    bool operator>(const TensorIndex& rhs) const { return compare(rhs) > 0; }
    
protected:
    std::vector<int> v;
    
    int compare(const TensorIndex &rhs) const
    {
        if(v.size() < rhs.v.size()) return -1;
        if(v.size() > rhs.v.size()) return 1;
        for(int i=0; i<v.size(); i++) {
            if(v[i]>rhs.v[i]) return 1;
            if(v[i]<rhs.v[i]) return -1;
        }
        
        //must be equal
        return 0;
    }
};
typedef TensorIndex TensorDimension;


class Tensor
{
public:
    Tensor(const TensorDimension & dims);
    
    //get the tensor's dimensions
    TensorDimension dim();
    
    //used as part of the general index strategy, this fixes dimensions to build an index
    class Accessor
    {
    public:
        Accessor operator[](int i);
        double operator=(double rhs);
        double operator+=(double rhs);
        double operator-=(double rhs);
        double operator*=(double rhs);
        double operator/=(double rhs);
        operator double();
    protected:
        Accessor(Tensor &t, TensorIndex &index) : t(t), index(index) { }
        Tensor &t;
        TensorIndex index;
        friend Tensor;
    };
    
    //index operation (start of the chain of accessors)
    Accessor operator[](int i);
   
    //multiply current tensor by a scalar
    Tensor & operator*=(double rhs);
    
    //divide current tensor by a scalar
    Tensor & operator/=(double rhs);
    
    //multiply by a scalar and return new tensor
    Tensor operator*(double rhs);
    
    //divide by a scalar and return new tensor
    Tensor operator/(double rhs);
    
    //add and asign tensor
    Tensor & operator+=(Tensor &rhs);
    
    //subtract and assign tensor
    Tensor & operator-=(Tensor &rhs);
    
    //add two tensors and return new tensor
    Tensor operator+(Tensor &rhs);
    
    //subtract two tensors and return new tensor
    Tensor operator-(Tensor &rhs);
    
    //compute the Frobenius Norm of the tensor
    double norm();
protected:
    std::map<TensorIndex,double> elements;
    TensorDimension d;
    friend Accessor;
};


#endif