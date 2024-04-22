#include <bits/stdc++.h>


 
#define ll long long int
#define ld long double
 
#define inf LONG_LONG_MAX
#define MOD 1e9+7
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define print(x) for(auto element:x) cout <<element << " ";
#define endl "\n"


 
using namespace std;

//freopen("file.txt","r",stdin);
//getline(cin,string);
//num % mod = (num % mod + mod) % mod
//rand() % (end - start + 1) + start;

struct Node{
    int value;
    Node* prev;
    Node* next;

    Node(int value, Node *prev, Node *next){
        this->value= value;
        this->prev = prev;
        this->next = next;
    }
};

struct Stack{
    Node* last;

    Stack(){
        this->last = new Node(-1,nullptr,nullptr);
    }

    bool empty(){
        return this->last->value == -1;
    }

    int top(){
        return this->last->value;
    }

    void push(int value){
        Node* curr = new Node(value,this->last,nullptr);
        this->last = curr;
    }

    void pop(){
        if (this->last->prev != nullptr){
            this->last = this->last->prev;
        }
    }
};
