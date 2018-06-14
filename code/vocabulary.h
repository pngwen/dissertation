#line 29 "influence.nw"
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

#ifndef VOCABULARY_H
#define VOCABULARY_H
class Vocabulary
{
public:
    
#line 81 "influence.nw"
Vocabulary();   //no argument constructor
#line 99 "influence.nw"
Vocabulary(const Vocabulary &rhs);
#line 42 "influence.nw"
    
#line 147 "influence.nw"
void add(const std::string &term);
void add(const std::string &term, int num);
#line 200 "influence.nw"
int size() const;
#line 216 "influence.nw"
std::map<std::string, int>::iterator begin();
std::map<std::string, int>::iterator end();
#line 43 "influence.nw"
    
#line 103 "influence.nw"
Vocabulary& operator=(const Vocabulary &rhs);
#line 244 "influence.nw"
int operator()(const std::string &term);
std::string operator()(int num);

#line 45 "influence.nw"
private:
    
#line 66 "influence.nw"
std::map<std::string, int> toNum;
std::map<int, std::string> toTerm;
#line 74 "influence.nw"
int nextNum;    //the next available index number
#line 47 "influence.nw"
};


#line 274 "influence.nw"
Vocabulary readVocabulary(std::istream &is);
void writeVocabulary(std::ostream &os, Vocabulary &v);
#line 51 "influence.nw"
#endif
