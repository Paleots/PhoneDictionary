#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Node{
public:
    Node():left(nullptr),eq(nullptr),right(nullptr),isEndOfString(1){}
    ~Node();
    
private:
    friend class PhoneBook;
    char data;
    unsigned isEndOfString;
    string number;
    Node* left,*eq,*right;
};


/*
class NodeWithNumber: public Node{
private:
    friend class PhoneBook;
    string number;
};

*/
#endif /* Node_hpp */

