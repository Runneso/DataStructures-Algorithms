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

pair<vector<ll>, vector<ll> > lcis(const vector<ll> &a, const vector<ll> &b) {
    ll n = a.size(), m = b.size();
    vector<ll> dp(m, 0), parent(m, -1), fromA(m, -1);

    for (ll index = 0; index < n; index++) {
        ll bestLen = 0, bestPos = -1;
        for (ll j = 0; j < m; j++) {
            if (b[j] < a[index]) {
                if (dp[j] > bestLen) {
                    bestLen = dp[j];
                    bestPos = j;
                }
            } else if (b[j] == a[index]) {
                ll candidate = bestLen + 1;
                if (candidate > dp[j]) {
                    dp[j] = candidate;
                    parent[j] = bestPos;
                    fromA[j] = index;
                }
            }
        }
    }

    ll endJ = -1, best = 0;
    for (ll index = 0; (size_t) index < b.size(); index++) {
        if (dp[index] > best) {
            best = dp[index];
            endJ = index;
        }
    }

    vector<ll> ia, ib;
    while (endJ != -1) {
        ib.push_back(endJ);
        ia.push_back(fromA[endJ]);
        endJ = parent[endJ];
    }
    
    reverse(all(ia));
    reverse(all(ib));
    return {ia, ib};
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
