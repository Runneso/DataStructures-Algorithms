#include <bits/stdc++.h>

using namespace std;

struct DSU {
    size_t n;
    vector<size_t> parents;
    vector<size_t> ranks;

    explicit DSU(const size_t n) {
        this->n = n;
        this->parents.assign(n, 0);
        this->ranks.assign(n, 0);

        for (size_t index = 0; index < n; ++index) {
            this->parents[index] = index;
        }
    }

    size_t find_set(const size_t v) {
        if (v == this->parents[v]) {
            return v;
        }
        this->parents[v] = find_set(this->parents[v]);
        return this->parents[v];
    }

    void unite(const size_t v1, const size_t v2) {
        size_t x = find_set(v1);
        size_t y = find_set(v2);

        if (x == y) {
            return;
        }

        if (this->ranks[x] < this->ranks[y]) {
            swap(x, y);
        }

        this->parents[y] = x;

        if (this->ranks[x] == this->ranks[y]) {
            this->ranks[x]++;
        }
    }
};
