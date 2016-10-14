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
    
    //provides access to the index element
    int & operator[](int i) { return v[i]; }
protected:
    std::vector<int> v;
};
typedef TensorIndex TensorDimension;


class TensorBase
{
public:
    virtual operator double &() { throw std::bad_cast(); }
    virtual double & operator=(double rhs) { throw std::bad_cast(); }
    virtual TensorBase &operator[](int i) = 0;
};


class Tensor : TensorBase
{
public:
    Tensor(std::vector<int> dims);
    virtual ~Tensor();
   
    //index operator works one dimension at a time
    virtual TensorBase &operator[](int i);
    
protected:
    std::map<int,TensorBase*> elements;
    std::vector<int> d;
};


class TensorScalar : public TensorBase
{
public:
    virtual operator double&() { return value; }
    virtual double & operator=(double rhs) { value=rhs; } 
    virtual TensorBase &operator[](int i) {throw std::out_of_range("Attempted index on scalar object."); }
protected:
    double value;
};
#endif