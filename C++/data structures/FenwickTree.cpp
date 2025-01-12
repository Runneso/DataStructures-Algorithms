#include <bits/stdc++.h>

using namespace std;

template<class T>
struct FenwickTree {
    int64_t n;
    vector<T> BIT;
    vector<T> array;

    function<T(T, T)> action;
    function<T(T, T)> reverse_action;

    explicit FenwickTree(vector<T> &seq, T action(T, T), T reverse_action(T, T)) {
        this->n = seq.size();
        this->BIT.assign(n, 0);
        this->array = vector<T>(seq);

        this->action = action;
        this->reverse_action = reverse_action;

        this->build();
    }

    explicit FenwickTree(vector<T> &seq) {
        this->n = seq.size();
        this->BIT.assign(n, 0);
        this->array = seq;

        this->action = [&](T a, T b) {
            return a + b;
        };
        this->reverse_action = [&](T a, T b) {
            return a - b;
        };

        this->build();
    }

    void build() {
        this->BIT = this->array;
        for (int64_t index = 0; index < n; ++index) {
            int64_t j = index | (index + 1);
            if (j < n) {
                BIT[j] = action(BIT[j], BIT[index]);
            }
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
            ans = this->action(ans, this->BIT[i]);
            i = (i & (i + 1)) - 1;
        }
        return ans;
    }

    T query(const int64_t l, const int64_t r) {
        if (l == 0) {
            return sum(r);
        }
        return this->reverse_action(this->sum(r), this->sum(l - 1));
    }
};
