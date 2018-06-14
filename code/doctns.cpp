#line 444 "influence.nw"
/* A utility to convert a document into a tensor.
   The command line arguments are: n vocabulary document.
   The output is printed to standard out. */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "tensor.h"
#include "vocabulary.h"

using namespace std;

int main(int argc, char** argv)
{
    
#line 492 "influence.nw"
Vocabulary v;     //the vocabulary
ifstream file;    //file for input
#line 514 "influence.nw"
int n;                //the number of modes
Tensor<>::Index dim;  //the tensor dimensions
Tensor<> t{};           //the document tensor
#line 559 "influence.nw"
string word;
vector<string> doc;
#line 578 "influence.nw"
Tensor<>::Index idx;

#line 461 "influence.nw"
    
#line 481 "influence.nw"
//handle errors
if(argc != 4) {
    cerr << "Usage: " << argv[0] << " n vocabulary document" << endl;
    exit(1);
}
#line 497 "influence.nw"
//open vocabulary file and check for errors
file.open(argv[2]);
if(!file) {
    cerr << "Could not open vocabulary file: " << argv[2] << endl;
    exit(3);
}

//read the vocabulary file
v = readVocabulary(file);

file.close();
#line 520 "influence.nw"
//get n-gram size
n = atoi(argv[1]);

//build the tensor dimensions
for(int i=0; i<n; i++) {
    dim.append(v.size());
}

//create the tensor
t = Tensor<>(dim);
#line 535 "influence.nw"
//open document and handle errors
file.open(argv[3]);
if(!file) {
    cerr << "Could not open document file: " << argv[3] << endl;
    exit(2);
}
#line 462 "influence.nw"
    
#line 564 "influence.nw"
while(file >> word) {
    doc.push_back(word);
}

//we are done with the file!
file.close();
#line 582 "influence.nw"
idx = Tensor<>::Index(n);  //create an n-element index
for(int i=0; i<doc.size()-n; i++) {
    //build the n-gram index from vocabulary and document
    for(int j=0; j<n; j++) { 
        idx[j] = v(doc[i+j])-1;
    }

    //add 1 to the frequency
    t[idx] += 1;
}
#line 463 "influence.nw"
    
#line 600 "influence.nw"
for(auto itr = t.sparseBegin(); itr != t.sparseEnd(); itr++) {
    if(*itr < 2.0) continue;
    //print the index
    idx=itr.index();
    
#line 613 "influence.nw"
for(int i=0; i<idx.size(); i++) {
    cout << (idx[i]+1) << '\t';
}

#line 606 "influence.nw"
    //print the element
    cout << *itr << endl;
}
#line 624 "influence.nw"
//handle the leading corner
idx = t.begin().index();
if(t[idx] <= 1.0) {
    
#line 613 "influence.nw"
for(int i=0; i<idx.size(); i++) {
    cout << (idx[i]+1) << '\t';
}
#line 628 "influence.nw"
    cout << 0.0 << endl;
}

//handle the trailing corner
idx = (t.end()-1).index();
if(t[idx] <= 1.0) {
    
#line 613 "influence.nw"
for(int i=0; i<idx.size(); i++) {
    cout << (idx[i]+1) << '\t';
}
#line 635 "influence.nw"
    cout << 0.0 << endl;
}
#line 464 "influence.nw"
}
