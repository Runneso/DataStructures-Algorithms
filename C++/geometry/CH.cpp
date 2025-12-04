#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll long long int
#define ld long double

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define MOD (1'000'000'000+7)
#define MOD_ (1'000'000'000+9)
#define BASE (911382323)
#define BASE_ (972663749)
#define EPS 1e-9
#define all(x) x.begin(), x.end()
#define print(x) for (auto element : x) cout << element << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;
#define RAMAZAN_RAKHMATULLIN_FAN_CLUB = true;

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;


// cross <= 0  -> strict hull: выкидываем коллинеарные на ребрах (оставляем только вершины/крайние)
// cross < 0   -> non-strict hull: сохраняем коллинеарные точки на границе (все точки на ребрах)
vector<Pt> convex_hull(vector<Pt> p) {
    ll n = p.size();
    if (n <= 1) {
        return p;
    }

    sort(p.begin(), p.end(), [](const Pt &a, const Pt &b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y;
    });

    p.erase(unique(p.begin(), p.end(), [](const Pt &a, const Pt &b) {
        return a.x == b.x && a.y == b.y;
    }), p.end());

    n = p.size();
    if (n <= 1) {
        return p;
    }

    vector<Pt> h;
    h.reserve(n * 2);

    for (ll index_i = 0; index_i < n; index_i++) {
        while (h.size() >= 2 && cross128(h[h.size() - 2], h.back(), p[index_i]) <= 0) {
            h.pop_back();
        }
        h.push_back(p[index_i]);
    }

    ll lower_size = h.size();

    for (ll index_i = n - 2; index_i >= 0; index_i--) {
        while (h.size() > lower_size && cross128(h[h.size() - 2], h.back(), p[index_i]) <= 0) {
            h.pop_back();
        }
        h.push_back(p[index_i]);
    }

    h.pop_back();
    return h;
}


void solution() {
}

int main() {
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin>>t;
    while (t--) {
        solution();
    }
}
