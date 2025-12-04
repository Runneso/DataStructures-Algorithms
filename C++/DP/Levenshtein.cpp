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

ll levenshtein(const string &a, const string &b) {
    const string *pa = &a, *pb = &b;

    if (pa->size() < pb->size()) {
        swap(pa, pb);
    }

    const string &s = *pa;
    const string &t = *pb;
    ll n = s.size(), m = t.size();

    vector<ll> prev(m + 1), cur(m + 1);

    for (ll index_j = 0; index_j <= m; index_j++) {
        prev[index_j] = index_j;
    }

    for (ll index_i = 1; index_i <= n; index_i++) {
        cur[0] = index_i;
        for (ll index_j = 1; index_j <= m; index_j++) {
            ll cost = (s[index_i - 1] == t[index_j - 1]) ? 0 : 1;
            ll deletion = prev[index_j] + 1;
            ll insertion = cur[index_j - 1] + 1;
            ll swapping = prev[index_j - 1] + cost;
            cur[index_j] = min(deletion, min(insertion, swapping));
        }
        prev.swap(cur);
    }

    return prev[m];
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
