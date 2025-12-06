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

struct PersistentKthSeg {
    struct Node {
        ll left, right;
        ll sum;
    };

    ll m;
    vector<Node> pool;
    vector<ll> roots;

    PersistentKthSeg() : m(0) {}

    ll new_node(ll L, ll R, ll sum) {
        pool.push_back({L, R, sum});
        return (ll)pool.size() - 1;
    }

    ll build(ll l, ll r) {
        if (l == r) return new_node(-1, -1, 0);
        ll mid = (l + r) / 2;
        ll L = build(l, mid);
        ll R = build(mid + 1, r);
        return new_node(L, R, 0);
    }

    ll update(ll node, ll l, ll r, ll pos) {
        if (l == r) return new_node(-1, -1, pool[(size_t)node].sum + 1);
        ll mid = (l + r) / 2;

        ll L = pool[(size_t)node].left;
        ll R = pool[(size_t)node].right;

        ll newL = L, newR = R;
        if (pos <= mid) newL = update(L, l, mid, pos);
        else            newR = update(R, mid + 1, r, pos);

        ll newSum = pool[(size_t)newL].sum + pool[(size_t)newR].sum;
        return new_node(newL, newR, newSum);
    }

    ll kth(ll leftRoot, ll rightRoot, ll l, ll r, ll k) {
        if (l == r) return l;
        ll mid = (l + r) / 2;

        ll lL = pool[(size_t)leftRoot].left;
        ll lR = pool[(size_t)rightRoot].left;

        ll cntLeft = pool[(size_t)lR].sum - pool[(size_t)lL].sum;

        if (k <= cntLeft) {
            return kth(lL, lR, l, mid, k);
        } else {
            ll rL = pool[(size_t)leftRoot].right;
            ll rR = pool[(size_t)rightRoot].right;
            return kth(rL, rR, mid + 1, r, k - cntLeft);
        }
    }

    void init(ll m_) {
        m = m_;
        pool.clear();
        roots.clear();
        if (m == 0) return;
        roots.push_back(build(0, m - 1)); // prefix 0
    }
};

void solution() {
    ll n, q;
    cin >> n >> q;
    vector<ll> a((size_t)n);
    for (ll i = 0; i < n; i++) cin >> a[(size_t)i];

    vector<ll> vals = a;
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());

    PersistentKthSeg pst;
    pst.init((ll)vals.size());

    for (ll i = 1; i <= n; i++) {
        ll x = a[(size_t)(i - 1)];
        ll pos = (ll)(lower_bound(all(vals), x) - vals.begin());
        ll newRoot = pst.update(pst.roots[(size_t)(i - 1)], 0, pst.m - 1, pos);
        pst.roots.push_back(newRoot);
    }

    while (q--) {
        ll l, r, k;
        cin >> l >> r >> k;          // обычно 1-indexed
        ll leftRoot = pst.roots[(size_t)(l - 1)];
        ll rightRoot = pst.roots[(size_t)r];
        ll idx = pst.kth(leftRoot, rightRoot, 0, pst.m - 1, k);
        cout << vals[(size_t)idx] << endl;
    }
}

int main() {
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin>>t;
    while (t--) solution();
}
