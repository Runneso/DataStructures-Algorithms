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

struct PersistentSegTree {
    struct Node {
        ll left, right, val;
    };

    ll n;
    vector<Node> pool;
    vector<ll> roots;

    PersistentSegTree(const vector<ll> &arr) {
        n = arr.size();
        pool.clear();
        roots.clear();
        ll root0 = build(0, n - 1, arr);
        roots.push_back(root0);
    }

    ll new_node(ll left, ll right, ll val) {
        pool.push_back({left, right, val});
        return pool.size() - 1;
    }

    ll build(ll l, ll r, const vector<ll> &arr) {
        if (l == r) {
            return new_node(-1, -1, arr[l]);
        }
        ll mid = (l + r) / 2;
        ll L = build(l, mid, arr);
        ll R = build(mid + 1, r, arr);
        return new_node(L, R, pool[L].val ^ pool[R].val);
    }

    // ll update(ll version, ll pos, ll value) {
    //     ll new_root = update_node(roots[version], 0, n - 1, pos, value);
    //     roots.push_back(new_root);
    //     return roots.size() - 1;
    // }

    ll update_node(ll node, ll l, ll r, ll pos, ll value) {
        if (l == r) {
            return new_node(-1, -1, value);
        }
        ll mid = (l + r) / 2;

        ll L = pool[node].left;
        ll R = pool[node].right;

        ll newL = L, newR = R;
        if (pos <= mid) {
            newL = update_node(L, l, mid, pos, value);
        } else {
            newR = update_node(R, mid + 1, r, pos, value);
        }

        ll newVal = pool[newL].val ^ pool[newR].val;
        return new_node(newL, newR, newVal);
    }

    // ll query(ll version, ll ql, ll qr) {
    //     return query_node(roots[version], 0, n - 1, ql, qr);
    // }

    ll query_node(ll node, ll l, ll r, ll ql, ll qr) {
        if (qr < l || r < ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return pool[node].val;
        }
        ll mid = (l + r) / 2;
        return query_node(pool[node].left, l, mid, ql, qr) ^ query_node(pool[node].right, mid + 1, r, ql, qr);
    }
};

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
