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


struct SegmentTree{
    int n;
    vector<int> tree;

    SegmentTree(vector<int> &seq){
        this->n=seq.size();
        this->tree = vector<int>(this->n*4,0);
        this->build(seq,0,this->n-1,0);
    }

    void build(vector<int> &seq,int left,int right,int index){
        if (left==right){
            this->tree[index]=seq[left];
            return;
        }

        int mid = (left+right)/2;

        this->build(seq,left,mid,2*index+1);
        this->build(seq,mid+1,right,2*index+2);

        this->tree[index]=this->tree[2*index+1]+this->tree[2*index+2];
    }

    void update(int left,int right,int index,int pos, int val){
        if (left==right){
            this->tree[index]=val;
            return;
        }

        int mid = (left+right)/2;

        if (pos<=mid){
            this->update(left,mid,2*index+1,pos,val);
        }else{
            this->update(mid+1,right,2*index+2,pos,val);
        }

        this->tree[index]=this->tree[2*index+1]+this->tree[2*index+2];
    }

    int sum(int left,int right,int index,int curr_left,int curr_right){
        if (curr_right<left || curr_left>right){
            return 0;
        }

        if (curr_left<=left && right<=curr_right){
            return this->tree[index];
        }

        int mid = (left+right)/2;

        int left_sum = this->sum(left,mid,2*index+1,curr_left,curr_right);
        int right_sum = this->sum(mid+1,right,2*index+2,curr_left,curr_right);

        return left_sum+right_sum;
    }
};