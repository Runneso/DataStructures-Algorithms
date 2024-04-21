#include "SegmentTree.cpp"

#include <bits/stdc++.h>

//freopen("file.txt","r",stdin);
//getline(cin,string);
//num % mod = (num % mod + mod) % mod
//rand() % (end - start + 1) + start;

int main(){
    srand(time(0));
    int n = 100;
    int tests=10e3;
    vector<int> array(n,0);
    for (int index=0;index<n;index++){
        array[index]=rand()%(int)(10e8+1);
    }
    SegmentTree tree{array};
    for (int test=0;test<tests;test++){
        int action = rand()%(2);
        if (action){
            int left = rand()%(n);
            int right = rand()%(n-left)+left;
            int correct_sum= 0;
            for (int index=left;index<=right;index++){
                correct_sum+=array[index];
            }
            assert(correct_sum==tree.sum(0,tree.n-1,0,left,right));
        }else{
            int pos = rand()%(n);
            int value = rand()%(int)(10e8+1);
            array[pos] = value;
            tree.update(0,tree.n-1,0,pos,value);
        }
    }

}