#line 61 "tensor.nw"
#ifndef TENSOR_H
#define TENSOR_H
#line 33 "tensor.nw"
#include <cmath>
#line 106 "tensor.nw"
#include <map>
#line 148 "tensor.nw"
#include <vector>
#line 163 "tensor.nw"
#include <initializer_list>
#line 381 "tensor.nw"
#include <exception>

#line 37 "tensor.nw"
template<typename E=double, E(*SQRT)(E)=std::sqrt>
#line 65 "tensor.nw"
                    class Tensor
{
public:
    //inner class prototypes
    
#line 122 "tensor.nw"
class Index;
#line 505 "tensor.nw"
class Accessor;
#line 670 "tensor.nw"
class Iterator;
#line 1012 "tensor.nw"
class SparseIterator;
#line 70 "tensor.nw"
    
    //constructors
    
#line 352 "tensor.nw"
Tensor(const Index &ubound)
  : ubound(ubound) { }
#line 362 "tensor.nw"
Tensor(std::initializer_list<int> dimensions)
  : Tensor(Index(dimensions)) { }
#line 73 "tensor.nw"
    
    //scalar operations
    
#line 1187 "tensor.nw"
virtual Tensor& operator*=(const E& s)
{
   //multiply all the "non-empty" cells
   for(auto itr = sparseBegin(); itr != sparseEnd(); itr++) {
      *itr *= s;
   }
   
   return *this;
}
#line 1204 "tensor.nw"
virtual Tensor operator*(const E& s)
{
   Tensor result(*this);
   
   return result*=s;
}
#line 1218 "tensor.nw"
virtual Tensor& operator/=(const E& s)
{
   //multiply all the "non-empty" cells
   for(auto itr = sparseBegin(); itr != sparseEnd(); itr++) {
      *itr= s;
   }
   
   return *this;
}
#line 1231 "tensor.nw"
virtual Tensor operator/(const E& s)
{
   Tensor result(*this);
   
   return result/=s;
}
#line 76 "tensor.nw"
    
    //tensor operations
    
#line 390 "tensor.nw"
virtual E get(const Index &index)
{
   
#line 431 "tensor.nw"
if(not index.within(ubound))
{
   throw std::out_of_range("Tensor index is out of range.");
}

#line 394 "tensor.nw"
   //find the element in the data map
   if(data.find(index) != data.end()) {
      return data[index];
   } else {
      return E();
   }
}
#line 411 "tensor.nw"
virtual void set(const Index &index, const E& value) 
{
   
#line 431 "tensor.nw"
if(not index.within(ubound))
{
   throw std::out_of_range("Tensor index is out of range.");
}

#line 415 "tensor.nw"
   //handle storage of the default value
   if(value == E()) {
      if(data.find(index) != data.end()) {
         data.erase(index);
      }
   } else {
      data[index] = value;
   }
}
#line 465 "tensor.nw"
virtual Accessor operator[](const Index &index) 
{
   
#line 431 "tensor.nw"
if(not index.within(ubound))
{
   throw std::out_of_range("Tensor index is out of range.");
}
#line 468 "tensor.nw"
   
   return Accessor(*this, index);
}
#line 487 "tensor.nw"
Accessor operator[](int i) 
{
   
#line 499 "tensor.nw"
Index index;
index.append(i);
#line 490 "tensor.nw"
   
   return Accessor(*this, index);
}
#line 642 "tensor.nw"
virtual Index dim() 
{
   return ubound;
}
#line 745 "tensor.nw"
virtual Iterator begin()
{
   return Iterator(Index(ubound.size(), 0), this);
}
#line 756 "tensor.nw"
virtual Iterator end()
{
   return Iterator(ubound, this);
}
#line 1081 "tensor.nw"
virtual SparseIterator sparseBegin()
{
    Index idx;   //the beginning index

    //Find the first non-sparse index (if there is one)
    if(data.empty()) {
       idx = ubound;
    } else {
        idx = data.begin()->first;
    }

    return SparseIterator(idx, this, &data);
}
#line 1101 "tensor.nw"
virtual SparseIterator sparseEnd()
{
    return SparseIterator(ubound, this, &data);
}
#line 1262 "tensor.nw"
virtual Tensor& operator+=(Tensor &rhs) 
{
   //the new fill value is the sum of the two fill values
   
#line 1276 "tensor.nw"
for(auto itr = sparseBegin(); itr != sparseEnd(); itr++) 
{
   *itr += rhs[itr.index()];
}
#line 1266 "tensor.nw"
   
#line 1287 "tensor.nw"
for(auto itr = rhs.sparseBegin(); itr != sparseEnd(); itr++) 
{
   if(data.find(itr.index()) == data.end()) {
      set(itr.index(), *itr);
   }
}
#line 1267 "tensor.nw"
   
   return *this;
}
#line 1301 "tensor.nw"
virtual Tensor operator+(Tensor &rhs) 
{
   Tensor result(*this);
   return result+=rhs;
}
#line 1313 "tensor.nw"
virtual Tensor& operator-=(Tensor &rhs) 
{
   
#line 1322 "tensor.nw"
for(auto itr = sparseBegin(); itr != sparseEnd(); itr++) 
{
   *itr -= rhs[itr.index()];
}
#line 1316 "tensor.nw"
   
#line 1329 "tensor.nw"
for(auto itr = rhs.sparseBegin(); itr != rhs.sparseEnd(); itr++) 
{
   if(data.find(itr.index()) == data.end()) {
      set(itr.index(), E() - *itr);
   }
}
#line 1317 "tensor.nw"
   return *this;
}
#line 1338 "tensor.nw"
virtual Tensor operator-(Tensor &rhs) 
{
   Tensor result(*this);
   return result-=rhs;
}
#line 1365 "tensor.nw"
virtual Tensor outer(Tensor &B)
{
    
#line 1381 "tensor.nw"
Tensor C(Index{dim(), B.dim()});
#line 1368 "tensor.nw"
    
#line 1401 "tensor.nw"
for(auto aitr = sparseBegin(); aitr!=sparseEnd(); aitr++) {
    for(auto bitr = B.sparseBegin(); bitr!=B.sparseEnd(); bitr++) {
        C.set(Index{aitr.index(), bitr.index()}, *aitr * *bitr);
    }
}

#line 1370 "tensor.nw"
    return C;
}
#line 79 "tensor.nw"
    
    //inner classes
    
#line 126 "tensor.nw"
class Index
{
public:
  //constructors
  
#line 158 "tensor.nw"
Index(std::vector<int> index) : v(index.begin(), index.end()) { }
#line 168 "tensor.nw"
Index(std::initializer_list<int> il) : v(il.begin(), il.end()) { }
#line 178 "tensor.nw"
Index(std::initializer_list<Index> il) 
{
    //append the lists
    for(auto itr = il.begin(); itr != il.end(); itr++) {
        append(*itr);
    }
}
#line 193 "tensor.nw"
Index(int n, int val=-1) : v(n, val) { }
#line 201 "tensor.nw"
Index() { /* do nothing */ }
#line 131 "tensor.nw"
  
  //vector operations
  
#line 211 "tensor.nw"
virtual int& operator[](int i) { return v[i]; }
virtual std::vector<int>::size_type size() const { return v.size(); }
#line 221 "tensor.nw"
virtual void append(int i) 
{
    v.push_back(i);
}
#line 233 "tensor.nw"
virtual void append(const Index& rhs) 
{
    v.reserve(v.size() + rhs.size());
    v.insert(v.end(), rhs.v.begin(), rhs.v.end());
}
#line 134 "tensor.nw"
  
  //comparison operations
  
#line 254 "tensor.nw"
int compare(const Index &rhs) const
{
   
#line 266 "tensor.nw"
if(size() < rhs.size()) return -1;
if(size() > rhs.size()) return 1;
#line 257 "tensor.nw"
   
#line 277 "tensor.nw"
for(int i=0; i<size(); i++) 
{
   //check for greater than
   if(v[i] > rhs.v[i]) 
   {
      //that's it!  We're done!
      return 1;
   }
   
   //check for less than
   if(v[i] < rhs.v[i])
   {
      return -1;
   }
}
#line 258 "tensor.nw"
   
   return 0;
}
#line 304 "tensor.nw"
virtual bool operator<(const Index &rhs)  const { return compare(rhs)  < 0; }
virtual bool operator<=(const Index &rhs) const { return compare(rhs) <= 0; }
virtual bool operator>(const Index &rhs)  const { return compare(rhs)  > 0; }
virtual bool operator>=(const Index &rhs) const { return compare(rhs) >= 0; }
virtual bool operator==(const Index &rhs) const { return compare(rhs) == 0; }
virtual bool operator!=(const Index &rhs) const { return compare(rhs) != 0; }
#line 318 "tensor.nw"
virtual bool within(const Index &bound) const
{
   //bounds must match
   if(size() != bound.size()) return false;
   
   for(int i=0; i<size(); i++) 
   {
      if(v[i]>=bound.v[i]) return false;
   }
   
   //all is good!
   return true;
}
#line 137 "tensor.nw"
  
private:
  
#line 152 "tensor.nw"
std::vector<int> v;
#line 140 "tensor.nw"
};
#line 509 "tensor.nw"
class Accessor 
{
public:
   
#line 573 "tensor.nw"
virtual Accessor operator[](int i)
{
   Accessor a(t, index);   //copy present accessor
   a.index.append(i);      //add to the end

   return a; //return the new accessor
}
#line 592 "tensor.nw"
virtual operator E()
{
   return t.get(index);
}
#line 608 "tensor.nw"
virtual E operator=(const E &rhs)
{
   t.set(index, rhs);
   return rhs;
}
#line 624 "tensor.nw"
virtual E operator+=(const E &rhs) { return (*this) = (E)(*this) + rhs; }
virtual E operator-=(const E &rhs) { return (*this) = (E)(*this) - rhs; }
virtual E operator*=(const E &rhs) { return (*this) = (E)(*this) * rhs; }
virtual E operator/=(const E &rhs) { return (*this) = (E)(*this) / rhs; }
#line 513 "tensor.nw"
private:
   
#line 552 "tensor.nw"
Accessor(Tensor &t, const Index& index) : t(t), index(index) 
{
    if(index.size() > t.dim().size()) {
        throw std::out_of_range("Too many dimensions in Tensor Access");
    }
}
#line 515 "tensor.nw"
   
#line 541 "tensor.nw"
Tensor &t;
Index index;
#line 516 "tensor.nw"
   
#line 563 "tensor.nw"
friend Tensor;
#line 517 "tensor.nw"
};
#line 676 "tensor.nw"
class Iterator
{
public:
    
#line 714 "tensor.nw"
Iterator() 
{
   //do nothing
}
#line 724 "tensor.nw"
Iterator(const Iterator& rhs)
{
   cur = rhs.cur;
   t = rhs.t;
   ubound = rhs.ubound;
}
#line 735 "tensor.nw"
Iterator(const Index &cur, Tensor *t) : cur(cur), t(t), ubound(t->dim()) {} 
#line 680 "tensor.nw"
    
#line 774 "tensor.nw"
virtual Iterator& operator++()
{
   move(1);
   return *this;
}

virtual Iterator operator++(int) 
{
   Iterator result(*this);
   move(1);
   return result;
}
#line 792 "tensor.nw"
virtual Iterator& operator--()
{
   move(-1);
   return *this;
}


#line 800 "tensor.nw"
virtual Iterator operator--(int)
{
   Iterator result(*this);
   move(-1);
   return result;
}
#line 814 "tensor.nw"
virtual Iterator operator+(int rhs)
{
   Iterator result(*this);
   result.move(rhs);
   return result;
}


virtual Iterator operator-(int rhs)
{
   Iterator result(*this);
   result.move(-rhs);
   return result;
}
#line 681 "tensor.nw"
    
#line 972 "tensor.nw"
virtual bool operator<(const Iterator &rhs)  { return cur <  rhs.cur; }
virtual bool operator<=(const Iterator &rhs) { return cur <= rhs.cur; }
virtual bool operator>(const Iterator &rhs)  { return cur >  rhs.cur; }
virtual bool operator>=(const Iterator &rhs) { return cur >= rhs.cur; }
virtual bool operator==(const Iterator &rhs) { return cur == rhs.cur; }
virtual bool operator!=(const Iterator &rhs) { return cur != rhs.cur; }
#line 682 "tensor.nw"
    
#line 986 "tensor.nw"
virtual Accessor operator*()
{
   return (*t)[cur];
}
#line 996 "tensor.nw"
virtual Index index()
{
   return cur;
}
#line 683 "tensor.nw"
protected:
    
#line 691 "tensor.nw"
Index cur;  //current position
#line 697 "tensor.nw"
Tensor *t;  //the tensor we are iterating over
#line 705 "tensor.nw"
Index ubound; //the upper bound of the tensor we are iterating over
#line 838 "tensor.nw"
virtual void move(int d) 
{
    int i;          //a general index variable

    if(d > 0) 
    {
       
#line 891 "tensor.nw"
if(cur.size() > 1) {
    i = 1;
} else {
    i = 0;
}
#line 873 "tensor.nw"
while(i < cur.size()) {
    //increment the index, if is valid we are done!
    cur[i] += d;
    if(cur[i] < ubound[i]) {
        return;  
    }

    //Fix the overflow!
    d=cur[i]/ubound[i];
    cur[i] %= ubound[i];

    
#line 901 "tensor.nw"
if(i == 1) {
    i = 0;  //update the row next
} else if(i == 0) {
    i = 2;  //update the layer next
} else {
    i++;    //go to the next high-dimensional layer
}
#line 885 "tensor.nw"
}
#line 917 "tensor.nw"
cur = ubound;
#line 845 "tensor.nw"
    } 
    else if(d < 0) 
    {
       
#line 925 "tensor.nw"
if(cur == ubound) 
{
  for(int i=0; i<cur.size(); i++) 
  {
    cur[i]--;
  }
  d--;
}
#line 891 "tensor.nw"
if(cur.size() > 1) {
    i = 1;
} else {
    i = 0;
}
#line 941 "tensor.nw"
while(i < cur.size()) {
    //increment and validate
    cur[i]+=d;
    if(cur[i] >= 0) 
    {
        return;  //all done!
    } 
   
   //find out how much to "borrow" form the next column and adjust this
   //column accordingly
   d = cur[i] / ubound[i] - (cur[i] % ubound[i] ? 1 : 0);
   cur[i] += ubound[i] * -d;

   
#line 901 "tensor.nw"
if(i == 1) {
    i = 0;  //update the row next
} else if(i == 0) {
    i = 2;  //update the layer next
} else {
    i++;    //go to the next high-dimensional layer
}
#line 955 "tensor.nw"
}
#line 849 "tensor.nw"
    }
}
#line 685 "tensor.nw"
};
#line 1016 "tensor.nw"
class SparseIterator : public Iterator
{
public:
    
#line 1046 "tensor.nw"
SparseIterator()
{
    //do nothing
}
#line 1056 "tensor.nw"
SparseIterator(const SparseIterator &rhs) : Iterator(rhs)
{
    dptr = rhs.dptr;
}
#line 1071 "tensor.nw"
SparseIterator(const Index &cur, Tensor *t, std::map<Index, E> *dptr)
  : Iterator(cur, t), dptr(dptr) { }

#line 1021 "tensor.nw"
protected:
    
#line 1119 "tensor.nw"
virtual void move(int d)
{
    typename std::map<Index, E>::iterator itr;   //map iterator

    
#line 1136 "tensor.nw"
(*dptr)[Iterator::cur];  //get the element in the map (perhaps temporarily)
itr = dptr->find(Iterator::cur);  //get an iterator to that index
#line 1124 "tensor.nw"
    
#line 1143 "tensor.nw"
if(d < 0) {
    //move backwards
    itr--;
} else  {
    //move forwards
    itr++;
}
#line 1156 "tensor.nw"
if(itr == dptr->end()) {
    Iterator::cur = Iterator::t->dim();
} else {
    Iterator::cur = itr->first;
}
#line 1125 "tensor.nw"
    
#line 1167 "tensor.nw"
if(itr->second == E()) {  //remove zero elements
    dptr->erase(itr->first);
}
#line 1126 "tensor.nw"
}
#line 1023 "tensor.nw"
    
#line 1035 "tensor.nw"
std::map<Index, E> *dptr;
#line 1024 "tensor.nw"
};
#line 82 "tensor.nw"
    
private:
    
#line 110 "tensor.nw"
std::map<Index, E> data;
#line 342 "tensor.nw"
Index ubound;   //The dimension upper bound
#line 85 "tensor.nw"
};

#endif
