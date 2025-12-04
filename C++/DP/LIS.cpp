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

vector<ll> lis(const vector<ll> &arr, bool nondecreasing = false) {
    ll n = arr.size();
    vector<ll> d;
    vector<ll> pos;
    vector<ll> parent(n, -1);

    d.reserve(n);
    pos.reserve(n);

    for (ll index = 0; index < n; index++) {
        ll x = arr[index];
        ll j = nondecreasing
                   ? (upper_bound(d.begin(), d.end(), x) - d.begin())
                   : (lower_bound(d.begin(), d.end(), x) - d.begin());

        if (j > 0) parent[index] = pos[j - 1];

        if (j == d.size()) {
            d.push_back(x);
            pos.push_back(index);
        } else {
            d[j] = x;
            pos[j] = index;
        }
    }

    vector<ll> indexes;
    if (!pos.empty()) {
        int cur = pos.back();
        while (cur != -1) {
            indexes.push_back(cur);
            cur = parent[cur];
        }
        reverse(indexes.begin(), indexes.end());
    }
    return indexes;
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
