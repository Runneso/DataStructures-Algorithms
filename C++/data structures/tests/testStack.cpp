#include "../Stack.cpp"

#include <bits/stdc++.h>

//freopen("file.txt","r",stdin);
//getline(cin,string);
//num % mod = (num % mod + mod) % mod
//rand() % (end - start + 1) + start;

int main(){
    srand(time(0));
    int tests = 10e6;
    Stack stack;
    vector<int> array;
    for(int test=0;test<tests;test++){
        int action = rand()%(3);
        switch(action){
            case 0:{
                if (!stack.empty()){
                    assert(stack.top()==array.back());
                }
                break;
            }
            case 1:{
                int curr =rand()%(int)(10e6+1);
                stack.push(curr);
                array.push_back(curr);
                break;
            }
                
            case 2:{
                if (!stack.empty()){
                    stack.pop();
                    array.pop_back();
                }
                break;  
            }
            default: break;
        }
    }
}