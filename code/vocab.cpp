#line 317 "influence.nw"
/* A filter tool for extracting a vocabulary from stdin.
 */
#include <iostream>
#include <string>
#include "vocabulary.h"

using namespace std;

int main()
{
    Vocabulary v;
    string term;

    
#line 340 "influence.nw"
while(cin >> term) {
    v.add(term);
}

#line 332 "influence.nw"
    writeVocabulary(cout, v);
}
