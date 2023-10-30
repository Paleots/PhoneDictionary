#include "PhoneBook.hpp"
#include <fstream>
#include <sstream>
#include <list>
#include "PhonebookException.hpp"
#define _CRT_SECURE_NO_WARNINGS
#define MAX 200

//Fja. za ubacivanje u stablo
void PhoneBook::insert(Node ** root, char * word,const string& t){//,const string& number){
    try{
        if (t.length()<10 || t.length()>17) throw (new Exceptions("The contact does not have a valid number") );
        if(t[0] != '+'){
            if(t[0] != '0') throw (new Exceptions("The contact does not have a valid number, I skipped it"));
        }
        
        if(t[0] != '0'){
            if(t[0] != '+') throw (new Exceptions("The contact does not have a valid number, I skipped it"));
        }
        int j = 0;
        int zarez = 0;
        while(word[j]){
            if (word[j] == ',') zarez++;
            j++;
        }
        if(zarez>0){throw (new Exceptions("Incorrectly entered name") );}
    }
    catch (Exceptions* e){ e->print(); return;}
    if (!(*root))
             (*root) = newNode(*word);
    
    if((*word)<(*root)->data){
        insert(&( (*root)->left ), word,t);
        
    }else if((*word) >(*root)->data){
        insert(&( (*root)->right ), word,t);
        
    }else{
        if(*(word+1)) insert(&( (*root)->eq ), word+1,t); // razlicito
    
        else{
            (*root)->isEndOfString = 1;
            (*root)->number = t;
            
        }
    }
}
//---------------------------------------------------------------

//Fja. koja pravi novi cvor
Node* PhoneBook::newNode(char data){
    Node* temp1 = new Node();
    temp1->data = data;
    temp1->isEndOfString = 0;
    return temp1;
}
//---------------------------------------------------------------

//Fja. koja ucitava celo stablo
void PhoneBook::loadPhonebook(const string& filepath) {
        ifstream input(filepath);
        if (input.is_open()) {
            string given_str;
            string delim = ",";
            int j = 0;
            while (getline(input, given_str)) {
                try{
                    j++;
                    if(j%1000000==0) cout<< j << endl;
                    string token1, token2,token3;
                    int pos = 0;
                    int zarez = 0;
                    for (int i = 0; i < given_str.length(); i++) {
                        if (given_str[i] == ',') {pos = i+1;zarez++;}
                    }
                    
                    if(zarez>1) throw (new Exceptions("There is a contact with an incorrectly entered name, I skipped it") );
                    // ovi try catch blokovi su ovde jer zelim da nastavim sa upisom cak i kada ima gresaka
                    token1 = given_str.substr(0, pos-1); // store the substring
                    token2 = given_str.substr(pos, pos + given_str.length());
                    
                    if(token2[0] != '+'){
                        if(token2[0] != '0') throw (new Exceptions("The contact does not have a valid number, I skipped it"));
                    }
                    
                    if(token2[0] != '0'){
                        if(token2[0] != '+') throw (new Exceptions("The contact does not have a valid number, I skipped it"));
                    }
                    
                    
                    if (token2.length()<10 || token2.length()>17) throw (new Exceptions("The contact does not have a valid number, I skipped it") );
                    /*
                    int size = token1.length();
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = token1[i];
                    }
                    array[size] = '\0';
                    */
                    char array[200];
                    strcpy(array, token1.c_str());

                    insert(&root_,array,token2);
                }catch (Exceptions* e){ e->print(); continue;}
                
            }
        } else {cout<<"Nije moguce otvoriti fajl"<<endl; openFileCheck = "NOT OPEN";};
}
//------------------------------------------------


//obilazi celo stablo i skuplja sva imena
void PhoneBook::traverseTST(Node *root){
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0);
}
void PhoneBook::traverseTSTUtil(Node* root, char* buffer, int depth)
{
    if (root) // ovde isto kao moze da se doda izuzetak
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth);
 
        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }
 
        // Traverse the subtree using equal pointer (middle subtree)
        traverseTSTUtil(root->eq, buffer, depth + 1);
 
        // Finally Traverse the right subtree
        traverseTSTUtil(root->right, buffer, depth);
    }
}
//------------------------------------------------------------


//Pretrazuje da li rec postoji i vraca 1 ako postoji
int PhoneBook::searchTST(struct Node *root, char *word)
{
    if (!root)
        return 0;
 
    if (*word < (root)->data)
        return searchTST(root->left, word);
 
    else if (*word > (root)->data)
        return searchTST(root->right, word);
 
    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;
 
        return searchTST(root->eq, word+1);
    }
}
//-----------------------------------------------------------


//Uzima broj od kontakta
string PhoneBook::searchTSTstring(struct Node *root, char *word)
{
    if (!root)
        return "----- Ne postoji broj";
 
    if (*word < (root)->data)
        return searchTSTstring(root->left, word);
 
    else if (*word > (root)->data)
        return searchTSTstring(root->right, word);
 
    else
    {
        if (*(word+1) == '\0')
            return root->number;
 
        return searchTSTstring(root->eq, word+1);
    }
}
//------------------------------------------------------------


//fja. koja prati ovu gornju
void PhoneBook::print(){
    traverseTST(root_);
}


//-------------------------------------------------------------
// fja. koja kreira nova kontakt
void PhoneBook::newContact(char* t1,const string& t2) {
    insert(&root_,t1,t2);
}

//---------------------------------------------------------------


//fja. koja ako rec postoji ispisuje FOUND ili NOT FOUND
void PhoneBook:: select(char* t){
    if(searchTST(root_, t)) cout<<"FOUND"<<endl;else cout<<"NOT FOUND"<<endl;//}else cout<<"nije pronasao"<<endl;
}
//---------------------------------------------------------------

//Slicna kao fja. iznad samo sto ovog puta kada pronadje vraca string da li je pronasla
string PhoneBook::select_return_string(char* t){
    string c;
    if(searchTST(root_, t)) c="FOUND";else c="NOT FOUND"; //ovde moze izuzetak ako ne vrati FOUND
    return c;
}
//---------------------------------------------------------------


//uzima broj zadatog kontakta
void PhoneBook:: writeNumber(char* word){
    cout<<searchTSTstring(root_, word)<<endl;
}
//---------------------------------------------------------------


//fja. iz zadatka za pretrazivanje
void PhoneBook:: search(char*t){    
    if(t != ""){
        int i = 0 ;
        string c ;
        while(t[i+1]){
            c.push_back(t[i]);
            i++;
        }
        string g;
        // i  =0;
        while(t[i]){
            g.push_back(t[i]);
            i++;
        }
        traverseTST2( searchTSTforSearch(root_,t),c,g);
    }else write_every_contact();
    
}
//---------------------------------------------------------------------



//Modifikovana verzija obilaska , gde se sada prosledjuje jos jedan string koji predstavlja deo reci, kroz pregled searcha se ustanovi o cemu se radi
void PhoneBook::traverseTST2(Node *root,string& t,string& c){
    char buffer[MAX];
    traverseTSTUtil2(root, buffer, 0,t,c);
}
//---------------------------------------------------------------



//Modifikovana verzija obilaska , pomocna fja. koja pored toga sto sakuplja imena leksikografski , ispisuje dodatno i broj od kontakta kada ga pronadje
void PhoneBook::traverseTSTUtil2(Node* root, char* buffer, int depth,string& t,string& c)
{
    if (root)
    {
        traverseTSTUtil2(root->left, buffer, depth,t,c);

        buffer[depth] = root->data;
        if (root->isEndOfString){
            buffer[depth+1] = '\0';
            int  i = 0;
            string h;
            while(buffer[i]){
                h.push_back(buffer[i]);
                i++;
            }
            //bool found = h.find(c) != std::string::npos;
            bool found = false ;
            string c1 = c;
            if(h[0] == c[0] ){ found  = true;}
            if(found){
                string temp = t+h;
                char array[200];
                strcpy(array,temp.c_str());
                cout<<temp<<" ";
                writeNumber(array);
            }
                    
        }
 
        traverseTSTUtil2(root->eq, buffer, depth + 1,t,c);
        traverseTSTUtil2(root->right, buffer, depth,t,c);
    }
}


//---------------------------------------------------------------------

// Vraca adresu cvora gde se nalazi broj kontakta, koristi fje. koje sam vec prosao
Node* PhoneBook::searchTSTforSearch(Node *root, char *word){
    if (!root)
        return nullptr;
 
    if (*word < (root)->data)
        return searchTSTforSearch(root->left, word);
 
    else if (*word > (root)->data)
        return searchTSTforSearch(root->right, word);
 
    else
    {
        if (*(word+1) == '\0')
            return root;
 
        return searchTSTforSearch(root->eq, word+1);
    }
}

//---------------------------------------------------------------


//Fja. iz zadatka , brise kontakt koristi pomocne fje. koje sam gore prosao
void PhoneBook::deleteContact(char * t){
    if(select_return_string(t) == "FOUND"){
        Node* t1 = searchTSTforSearch(root_,t);
        t1->isEndOfString = 0;
    } else cout<<"NOT FOUND"<<endl;
}

//---------------------------------------------------------------


// Fja. iz zadatka, nista specijalna , sklopljena sa od ovih prethodnih fja.
void PhoneBook::edit(char* name,char* change){
    if(select_return_string(name) == "FOUND"){
        if(change[0] == '+' || change[0] == '0'){
            Node* t = searchTSTforSearch(root_,name);
            string h;
            int i = 0;
            while(change[i]){
                h.push_back(change[i]);
                i++;
            }
            t->number = h; //  change;
        }else{
            string c = searchTSTstring(root_, name);
            deleteContact(name);
            insert(&root_, change, c);
        }
        
    }else cout<<"Nije moguce"<<endl;
}
//---------------------------------------------------------------

//Fja iz zadatka, koja korsit listu iz private dela klase i tu skladisti kontakte nakon poziva
void PhoneBook::call(char * t){
    if(select_return_string(t) == "FOUND"){
        if(history_of_calls.size() == 10){
            history_of_calls.pop_back();
        }
        history_of_calls.push_front(t);
    }
}
//---------------------------------------------------------------


//prolazi kroz sve clanove liste i ispisuje ih
void PhoneBook::call_history(){
    for(const auto& name : history_of_calls){
       /*
        char array[name.length()];
        int  i = 0;
        while(name[i]){
            array[i] = name[i];
            i++;
        }
        array[name.length()] = '\0';
        */
        char array[200];
        strcpy(array, name.c_str());
        string c = searchTSTstring(root_, array);
    cout << name << " "<< c << endl;
    }
}

//---------------------------------------------------------------


//Destruktor
PhoneBook::~PhoneBook(){
    deleteTree(root_);
    this->root_ = nullptr;
}

//---------------------------------------------------------------


//Fja. koja se zove u destruktoru, postorder nacin obilska samo sto sada proveravamo i za jos jedan pokazivac
void PhoneBook::deleteTree(Node * root){
    if(openFileCheck!= "NOT OPEN"){
        if(root->left != nullptr) deleteTree(root->left);
        if(root->eq != nullptr) deleteTree(root->eq);
        if(root->right != nullptr) deleteTree(root->right);
        delete root;
    }else delete root;
    
}
//---------------------------------------------------------------

//Ime samo kaze
void PhoneBook:: write_every_contact(){
    traverseTST3(root_);
}

//---------------------------------------------------------------


//Ista kao traverseTST samo sto ona poziva drugu pomocnu fju. koja ispisuje pored imena i broj
void PhoneBook::traverseTST3(Node *root){
    char buffer[MAX];
    traverseTSTUtil3(root, buffer, 0);
}
void PhoneBook::traverseTSTUtil3(Node* root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil3(root->left, buffer, depth);
 
        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth+1] = '\0';
            cout<<buffer<<" ";
            writeNumber(buffer);
        }
 
        // Traverse the subtree using equal pointer (middle subtree)
        traverseTSTUtil3(root->eq, buffer, depth + 1);
 
        // Finally Traverse the right subtree
        traverseTSTUtil3(root->right, buffer, depth);
    }
}
//---------------------------------------------------------------

void PhoneBook::openTerminal(){
    if(openFileCheck != "NOT OPEN"){
        cout<<"--------------------------"<<endl;
        cout<<"Welcome to Your phonebook!"<<endl;
        cout<<"--------------------------"<<endl;
        bool p = true;
        while(p){
            string c;
            cout<<"Enter the command: ";
            getline(cin,c);
            if(c == "EXIT"){p = false;}
            if(c!="EXIT"){
                if(c=="SEARCH"){
                    cout<<"Enter the contact name: ";
                    
                    string g;
                    getline(cin,g);
                    if(g!=""){
                        /*
                        int size = g.length();
                        char array[size];
                        for(int i=0; i<size; i++){
                            array[i] = g[i];
                        }
                        array[size] = '\0';
                        */
                        char array[200];
                        strcpy(array, g.c_str());
                        search(array);
                    }
                    else { char t[] = ""; search(t); }
                }
                if(c=="SELECT"){
                    cout<<"Enter the contact name: ";
                    string g;
                    getline(cin,g);
                    /*
                    int size = g.length();
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = g[i];
                    }
                    array[size] = '\0';
                    */
                    char array[200];
                    strcpy(array, g.c_str());
                    select(array);
                }
                if(c=="DELETE"){
                    cout<<"Enter the contact name: ";
                    string g;
                    getline(cin,g);
                    int size = g.length();
                    /*
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = g[i];
                    }
                    array[size] = '\0';
                    */
                    char array[200];
                    strcpy(array, g.c_str());
                    deleteContact(array);
                }
                if(c=="NEW"){
                    string p;
                    cout<<"Enter the contact name: ";
                    getline(cin,p); cout<<endl;
                    cout<<"Enter the contact number: ";
                    string g;
                    getline(cin,g);cout<<endl;
                    /*
                    int size = p.length();
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = p[i];
                    }
                    array[size] = '\0';
                    */
                    char array[200];
                    strcpy(array, p.c_str());
                    newContact(array, g);
                }
                if(c=="EDIT"){
                    //void edit(char* want,char* change);
                    cout<<"Enter number/name you want to change: ";
                    string c;
                    getline(cin,c);
                    /*
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = c[i];
                    }
                    array[size] = '\0';
                    */
                    int size = c.length();
                    char array[200];
                    strcpy(array,c.c_str());
                    array[size] = '\0';
                    cout<<"Type what you want to set:";
                    string g;
                    getline(cin,g);
                    /*
                    size = g.length();
                    char array1[size];
                    for(int i=0; i<size; i++){
                        array1[i] = g[i];
                    }
                    array1[size] = '\0';
                    */
                    int size1 = g.length();
                    char array1[200];
                    strcpy(array1, g.c_str());
                    array1[size1] = '\0';
                    edit(array, array1);
                }
                if(c=="CALL"){
                    cout<<"The name of the person you want to call: ";
                    string g;
                    getline(cin,g);
                    /*
                    int size = g.length();
                    char array[size];
                    for(int i=0; i<size; i++){
                        array[i] = g[i];
                    }
                    array[size] = '\0';*/
                    char array[200];
                    strcpy(array,g.c_str());
                    call(array);
                }
                if(c=="CALL_HISTORY"){
                    cout<<"Your call history: "<<endl;
                    call_history();
                }
            }
            cout<<"*** FUCNTION DONE ***"<<endl;
        }
        cout<<"***PHONEBOOK CLOSED***"<<endl;
    }
}
/*
char* PhoneBook::converter(const string & t){
    int size = t.length();
    char array[size];
    for(int i=0; i<size; i++){
        array[i] = t[i];
    }
    array[size] = '\0';
    return array;
}*/
