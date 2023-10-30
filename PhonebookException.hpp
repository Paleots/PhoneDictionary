//
//  PhonebookException.hpp
//  Dz2
//
//  Created by Vukasin Pantic on 21.12.2022..
//

#ifndef PhonebookException_hpp
#define PhonebookException_hpp

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

class Exceptions{
public:
    Exceptions(const string& greska):c(greska){}
    void print();
private:
    string c;
};
#endif /* PhonebookException_hpp */
