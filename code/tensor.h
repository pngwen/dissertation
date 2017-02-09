#line 42 "tensor.nw"
#ifndef TENSOR_H
#define TENSOR_H
#line 29 "tensor.nw"
#include <cmath>
#line 88 "tensor.nw"
#include <map>
#line 130 "tensor.nw"
#include <vector>
#line 145 "tensor.nw"
#include <initializer_list>
#line 358 "tensor.nw"
#include <exception>
#line 572 "tensor.nw"
#include <typeinfo>

#line 33 "tensor.nw"
template<typename E=double, E(*SQRT)(E)=std::sqrt>
#line 46 "tensor.nw"
                    class Tensor
{
public:
    //inner class prototypes
    
#line 104 "tensor.nw"
class Index;
#line 437 "tensor.nw"
class Accessor;
#line 670 "tensor.nw"
class Iterator;
#line 51 "tensor.nw"
    
    //constructors
    
#line 306 "tensor.nw"
Tensor(const Index &ubound, E fillValue=E()) 
  : ubound(ubound), fillValue(fillValue) { }
#line 315 "tensor.nw"
Tensor(std::initializer_list<int> dimensions, E fillValue=E())
  : Tensor(Index(dimensions), fillValue) { }
#line 54 "tensor.nw"
    
    //scalar operations
    
#line 968 "tensor.nw"
Tensor& operator*=(const E& s)
{
   //multiply the "empty" cells
   fillValue *= s;
   
   //multiply all the "non-empty" cells
   for(auto itr = data.begin(); itr != data.end(); itr++) 
   {
      itr->second *= s;
      
#line 987 "tensor.nw"
//cleanup if this has become the fillValue!
if(itr->second == fillValue) 
{
   data.erase(itr);
}
#line 978 "tensor.nw"
   }
   
   return *this;
}
#line 1000 "tensor.nw"
Tensor operator*(const E& s)
{
   Tensor result(*this);
   
   return result*=s;
}
#line 1014 "tensor.nw"
Tensor& operator/=(const E& s)
{
   //multiply the "empty" cells
   fillValue /= s;
   
   //multiply all the "non-empty" cells
   for(auto itr = data.begin(); itr != data.end(); itr++) 
   {
      itr->second /= s;
      
#line 987 "tensor.nw"
//cleanup if this has become the fillValue!
if(itr->second == fillValue) 
{
   data.erase(itr);
}
#line 1024 "tensor.nw"
   }
   
   return *this;
}
#line 1032 "tensor.nw"
Tensor operator/(const E& s)
{
   Tensor result(*this);
   
   return result/=s;
}
#line 57 "tensor.nw"
    
    //tensor operations
    
#line 330 "tensor.nw"
void setFillValue(E val) 
{
   this->fillValue = val;
}
#line 341 "tensor.nw"
void fill(E val)
{
   setFillValue(val);
   data.clear();
}
#line 384 "tensor.nw"
virtual Accessor operator[](const Index &index) 
{
   
#line 397 "tensor.nw"
if(not index.within(ubound))
{
   throw std::out_of_range("Tensor index is out of range.");
}
#line 387 "tensor.nw"
   
   return Accessor(*this, index);
}
#line 416 "tensor.nw"
Accessor operator[](int i) 
{
   
#line 431 "tensor.nw"
Index index(ubound.size(), -1);
index[0] = i;
#line 419 "tensor.nw"
   
#line 397 "tensor.nw"
if(not index.within(ubound))
{
   throw std::out_of_range("Tensor index is out of range.");
}
#line 420 "tensor.nw"
   
   return Accessor(*this, index);
}
#line 651 "tensor.nw"
Index dim() 
{
   return ubound;
}
#line 745 "tensor.nw"
Iterator begin()
{
   return Iterator(Index(ubound.size(), 0), this);
}
#line 756 "tensor.nw"
Iterator end()
{
   return Iterator(ubound, this);
}
#line 1060 "tensor.nw"
Tensor& operator+=(Tensor &rhs) 
{
   //the new fill value is the sum of the two fill values
   E newFill = fillValue + rhs.fillValue;
   
   
#line 1081 "tensor.nw"
for(auto itr = data.begin(); itr != data.end(); itr++) 
{
   itr->second += rhs[itr->first];
}
#line 1066 "tensor.nw"
   
#line 1092 "tensor.nw"
for(auto itr = rhs.data.begin(); itr != rhs.data.end(); itr++) 
{
   if(data.find(itr->first) == data.end()) {
      data[itr->first] = fillValue + itr->second;
   }
}
#line 1067 "tensor.nw"
  
   //use the new fillValue
   fillValue = newFill;
   
   
#line 1164 "tensor.nw"
for(auto itr=data.begin(); itr != data.end(); itr++) 
{
   if(itr->second == fillValue) 
   {
      data.erase(itr);
   }
}
#line 1072 "tensor.nw"
   
   return *this;
}
#line 1106 "tensor.nw"
Tensor operator+(Tensor &rhs) 
{
   Tensor result(*this);
   return result+=rhs;
}
#line 1116 "tensor.nw"
Tensor& operator-=(Tensor &rhs) 
{
   //the new fill value is the sum of the two fill values
   E newFill = fillValue - rhs.fillValue;
   
   
#line 1136 "tensor.nw"
for(auto itr = data.begin(); itr != data.end(); itr++) 
{
   itr->second -= rhs[itr->first];
}
#line 1122 "tensor.nw"
   
#line 1143 "tensor.nw"
for(auto itr = rhs.data.begin(); itr != rhs.data.end(); itr++) 
{
   if(data.find(itr->first) == data.end()) {
      data[itr->first] = fillValue - itr->second;
   }
}
#line 1123 "tensor.nw"
  
   //use the new fillValue
   fillValue = newFill;
   
   
#line 1164 "tensor.nw"
for(auto itr=data.begin(); itr != data.end(); itr++) 
{
   if(itr->second == fillValue) 
   {
      data.erase(itr);
   }
}
#line 1128 "tensor.nw"
   
   return *this;
}
#line 1152 "tensor.nw"
Tensor operator-(Tensor &rhs) 
{
   Tensor result(*this);
   return result-=rhs;
}
#line 60 "tensor.nw"
    
    //inner classes
    
#line 108 "tensor.nw"
class Index
{
public:
  //constructors
  
#line 140 "tensor.nw"
Index(std::vector<int> index) : v(index.begin(), index.end()) { }
#line 150 "tensor.nw"
Index(std::initializer_list<int> il) : v(il.begin(), il.end()) { }
#line 159 "tensor.nw"
Index(int n, int val=-1) : v(n, val) { }
#line 167 "tensor.nw"
Index() { /* do nothing */ }
#line 113 "tensor.nw"
  
  //vector operations
  
#line 176 "tensor.nw"
int& operator[](int i) { return v[i]; }
std::vector<int>::size_type size() const { return v.size(); }
#line 116 "tensor.nw"
  
  //comparison operations
  
#line 194 "tensor.nw"
int compare(const Index &rhs) const
{
   
#line 206 "tensor.nw"
if(size() < rhs.size()) return -1;
if(size() > rhs.size()) return 1;
#line 197 "tensor.nw"
   
#line 217 "tensor.nw"
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
#line 198 "tensor.nw"
   
   return 0;
}
#line 244 "tensor.nw"
bool operator<(const Index &rhs)  const { return compare(rhs)  < 0; }
bool operator<=(const Index &rhs) const { return compare(rhs) <= 0; }
bool operator>(const Index &rhs)  const { return compare(rhs)  > 0; }
bool operator>=(const Index &rhs) const { return compare(rhs) >= 0; }
bool operator==(const Index &rhs) const { return compare(rhs) == 0; }
bool operator!=(const Index &rhs) const { return compare(rhs) != 0; }
#line 258 "tensor.nw"
bool within(const Index &bound) const
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
#line 119 "tensor.nw"
  
private:
  
#line 134 "tensor.nw"
std::vector<int> v;
#line 122 "tensor.nw"
};
#line 441 "tensor.nw"
class Accessor 
{
public:
   
#line 503 "tensor.nw"
Accessor operator[](int i)
{
   
#line 515 "tensor.nw"
int di;  //dimension index
for(di=0; di<index.size(); di++)
{
   if(index[di] == -1) {
     break;
   }
}
#line 529 "tensor.nw"
if(di == index.size()) throw std::out_of_range("Too many dimensions in Tensor Access");
#line 535 "tensor.nw"
if(i >= t.ubound[di]) throw std::out_of_range("Tensor index is out of range.");
#line 506 "tensor.nw"
   
#line 542 "tensor.nw"
Accessor a(t, index);
a.index[di] = i;  
#line 507 "tensor.nw"
   
   return a; //return the new accessor
}
#line 551 "tensor.nw"
operator E()
{
   
#line 562 "tensor.nw"
for(int i=0; i<index.size(); i++) 
{
   if(index[i] < 0) 
   {
      throw std::bad_cast();
   }
}
#line 554 "tensor.nw"
   
#line 579 "tensor.nw"
//absence means fill value
if(t.data.find(index) == t.data.end()) 
{
   return t.fillValue;
}

//return it!
return t.data[index];
#line 555 "tensor.nw"
}
#line 596 "tensor.nw"
E operator=(const E &rhs)
{
   
#line 604 "tensor.nw"
t.data[index] = rhs;
#line 611 "tensor.nw"
if(rhs == t.fillValue) 
{
   t.data.erase(index);
}
#line 621 "tensor.nw"
return rhs;
#line 599 "tensor.nw"
}
#line 633 "tensor.nw"
E operator+=(const E &rhs) { return (*this) = (E)(*this) + rhs; }
E operator-=(const E &rhs) { return (*this) = (E)(*this) - rhs; }
E operator*=(const E &rhs) { return (*this) = (E)(*this) * rhs; }
E operator/=(const E &rhs) { return (*this) = (E)(*this) / rhs; }
#line 445 "tensor.nw"
private:
   
#line 483 "tensor.nw"
Accessor(Tensor &t, const Index& index) : t(t), index(index) {}
#line 447 "tensor.nw"
   
#line 473 "tensor.nw"
Tensor &t;
Index index;
#line 448 "tensor.nw"
   
#line 490 "tensor.nw"
friend Tensor;
#line 449 "tensor.nw"
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
Iterator& operator++()
{
   move(1);
   return *this;
}

Iterator operator++(int) 
{
   Iterator result(*this);
   move(1);
   return result;
}
#line 792 "tensor.nw"
Iterator& operator--()
{
   move(-1);
   return *this;
}


#line 800 "tensor.nw"
Iterator& operator--(int)
{
   Iterator result(*this);
   move(-1);
   return result;
}
#line 814 "tensor.nw"
Iterator operator+(int rhs)
{
   Iterator result(*this);
   result.move(rhs);
   return result;
}


Iterator operator-(int rhs)
{
   Iterator result(*this);
   result.move(-rhs);
   return result;
}
#line 681 "tensor.nw"
    
#line 923 "tensor.nw"
bool operator<(const Iterator &rhs)  { return cur <  rhs.cur; }
bool operator<=(const Iterator &rhs) { return cur <= rhs.cur; }
bool operator>(const Iterator &rhs)  { return cur >  rhs.cur; }
bool operator>=(const Iterator &rhs) { return cur >= rhs.cur; }
bool operator==(const Iterator &rhs) { return cur == rhs.cur; }
bool operator!=(const Iterator &rhs) { return cur != rhs.cur; }
#line 682 "tensor.nw"
    
#line 937 "tensor.nw"
Accessor operator*()
{
   return (*t)[cur];
}
#line 947 "tensor.nw"
Index index()
{
   return cur;
}
#line 683 "tensor.nw"
private:
    
#line 691 "tensor.nw"
Index cur;  //current position
#line 697 "tensor.nw"
Tensor *t;  //the tensor we are iterating over
#line 705 "tensor.nw"
Index ubound; //the upper bound of the tensor we are iterating over
#line 838 "tensor.nw"
void move(int d) 
{
   if(d > 0) 
   {
      
#line 854 "tensor.nw"
for(int i=0; i<cur.size(); i++) 
{
   cur[i] += d;
   if(cur[i] < ubound[i]) 
   {
      return;  //done!
   }
   
   //Fix the overflow!
   d=cur[i]/ubound[i];
   cur[i] %= ubound[i];
}
#line 875 "tensor.nw"
cur = ubound;
#line 843 "tensor.nw"
   } 
   else if(d < 0) 
   {
      
#line 883 "tensor.nw"
if(cur == ubound) 
{
  for(int i=0; i<cur.size(); i++) 
  {
    cur[i]--;
  }
  d--;
}
#line 896 "tensor.nw"
for(int i=0; i<cur.size(); i++) 
{
   cur[i]+=d;
   if(cur[i] >= 0) 
   {
      return;  //all done!
   } 
   
   //find out how much to "borrow" form the next column and adjust this
   //column accordingly
   d = cur[i] / ubound[i] - (cur[i] % ubound[i] ? 1 : 0);
   cur[i] += ubound[i] * -d;
}
#line 847 "tensor.nw"
   }
}
#line 685 "tensor.nw"
};
#line 63 "tensor.nw"
    
private:
    
#line 92 "tensor.nw"
std::map<Index, E> data;
#line 288 "tensor.nw"
Index ubound;   //The dimension upper bound
#line 297 "tensor.nw"
E fillValue;
#line 66 "tensor.nw"
    
#line 493 "tensor.nw"
friend Accessor;
#line 67 "tensor.nw"
};

#endif
