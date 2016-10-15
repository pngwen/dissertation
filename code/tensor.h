﻿/*
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
    
    //comparison operations
    bool operator<(const TensorIndex& rhs) { return compare(rhs) < 0; }
    bool operator==(const TensorIndex& rhs) { return compare(rhs) == 0; }
    bool operator>(const TensorIndex& rhs) { return compare(rhs) > 0; }
    
protected:
    std::vector<int> v;
    
    int compare(const TensorIndex &rhs)
    {
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
    virtual ~Tensor();
    
    //used as part of the general index strategy
    
protected:
    std::map<int,double> elements;
    TensorDimension d;
    
};


#endif