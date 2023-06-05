#include <iostream>
#include <list>
using namespace std; 
class JobNode{
    public: 
    string name;
    list<string> *  users;
    string userMatched;
    JobNode(string name, string userName){
        this->name = name;
        this->users = new list<string>();
        this->users->push_back(userName);
    }
    void addUser(string userName){
        users->push_back(userName);
    }
    void matchUser(string userName){
        this->userMatched = userName;
    }
    JobNode(){};
    bool empty(){ return userMatched.empty();}
};