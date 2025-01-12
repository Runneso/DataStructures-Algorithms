#include <bits/stdc++.h>

using namespace std;

template<class T>
struct FenwickTree {
    int64_t n;
    vector<T> BIT;
    vector<T> array;

    explicit FenwickTree(vector<T> &seq) {
        this->n = seq.size();
        this->BIT.assign(n, 0);
        this->array = vector<T>(seq);
        this->build();
    }

    void build() {
        for (int64_t index = 0; index < this->n; ++index) {
            modify(index, this->array[index]);
        }
    }

    void modify(int64_t i, T val) {
        while (i < n) {
            BIT[i] += val;
            i = i | (i + 1);
        }
    }

    void set(int64_t i, T val) {
        T delta = val - this->array[i];
        this->array[i] = val;
        modify(i, delta);
    }

    T sum(int64_t i) {
        T ans = 0;
        while (i >= 0) {
            ans += this->BIT[i];
            i = (i & (i + 1)) - 1;
        }
        return ans;
    }

    T query(const int64_t l, const int64_t r) {
        return this->sum(r) - this->sum(l - 1);
    }
};
