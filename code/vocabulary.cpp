#line 56 "influence.nw"
#include "vocabulary.h"
#line 87 "influence.nw"
Vocabulary::Vocabulary() 
{
    nextNum = 0;   //begin at zero
}
#line 107 "influence.nw"
Vocabulary::Vocabulary(const Vocabulary &rhs) : Vocabulary()
{
    *this = rhs;
}
#line 116 "influence.nw"
Vocabulary& Vocabulary::operator=(const Vocabulary &rhs) 
{
    
#line 128 "influence.nw"
    toNum.clear();
    toTerm.clear();
    nextNum = 0;
#line 119 "influence.nw"
    
#line 135 "influence.nw"
for(auto itr=rhs.toNum.begin(); itr != rhs.toNum.end(); itr++) {
    add(itr->first, itr->second);
}

#line 121 "influence.nw"
    return *this;
}
#line 155 "influence.nw"
void Vocabulary::add(const std::string &term)
{
    //add using the nextNum as the number
    add(term, nextNum);
}
#line 164 "influence.nw"
void Vocabulary::add(const std::string &term, int num)
{
    
#line 176 "influence.nw"
if(toNum.find(term) != toNum.end() or toTerm.find(num) != toTerm.end()) 
{
   return;
}
#line 167 "influence.nw"
    
#line 185 "influence.nw"
toNum[term] = num;
toTerm[num] = term;
#line 168 "influence.nw"
    
#line 193 "influence.nw"
if(num >= nextNum) {
    nextNum = num+1;
}
#line 169 "influence.nw"
}
#line 204 "influence.nw"
int Vocabulary::size() const
{
    return toTerm.size();
}
#line 225 "influence.nw"
std::map<std::string, int>::iterator Vocabulary::begin()
{
    return toNum.begin();
}

std::map<std::string, int>::iterator Vocabulary::end()
{
    return toNum.end();
}
#line 251 "influence.nw"
int Vocabulary::operator()(const std::string &term) 
{
    return toNum[term];
}
#line 259 "influence.nw"
std::string Vocabulary::operator()(int num) 
{
    return toTerm[num];
}
#line 282 "influence.nw"
Vocabulary readVocabulary(std::istream &is) 
{
    Vocabulary v;
    std::string term;
    int num;

    //read until the end of the stream (or first error)
    while(is >> term>> num) {
        v.add(term, num);
    }

    return v;
}
#line 301 "influence.nw"
void writeVocabulary(std::ostream &os, Vocabulary &v)
{
    for(auto itr = v.begin(); itr != v.end(); itr++) {
        os << itr->first << '\t' << itr->second << std::endl;
    }
}
