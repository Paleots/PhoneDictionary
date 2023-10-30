#ifndef PhoneBook_hpp
#define PhoneBook_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "Node.hpp"
#include <list>
using namespace std;

class PhoneBook{
public:
    void loadPhonebook(const string& filepath);
    PhoneBook():root_(nullptr){}
    virtual ~PhoneBook();
    void newContact(char *,const string&);
    void select(char*);
    void deleteContact(char*);
    void edit(char* want,char* change);
    void call(char *);
    void call_history();
    void openTerminal();
    
    
    void search(char*);
  
private:
    char* converter(const string&);
    void deleteTree(Node*);
    void insert(Node**, char*,const string& t);
    string select_return_string(char*);
    void writeNumber(char*);
    Node* searchTSTforSearch(Node *root, char *word);
    void traverseTST_Advenced(Node* root,string& );
    void traverseTSTUtil2(Node* root, char* buffer, int depth,string&,string& );
    void traverseTST2(Node *root,string&,string&);
    string searchTSTstring(Node *root, char *word);
    Node* newNode(char data);
    void print();
    void traverseTSTUtil(Node* root, char* buffer, int depth);
    void traverseTST(Node* root);
    int searchTST(Node *root, char *word);
    void insertSpecialNode(Node ** root, char * word,const string&);
    void traverseTST3(Node *root);
    void write_every_contact();
    void traverseTSTUtil3(Node* root, char* buffer, int depth);
    string openFileCheck;
    list<string> history_of_calls;
    Node* root_;
};
#endif


