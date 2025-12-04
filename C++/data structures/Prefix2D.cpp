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


struct Prefix2D {
    vector<vector<ll> > prefix;

    explicit Prefix2D(const vector<vector<ll> > &matrix) {
        ll n = matrix.size();
        ll m = matrix[0].size();

        prefix.assign(n + 1, vector<ll>(m + 1, 0));

        for (ll index_i = 1; index_i <= n; index_i++) {
            ll row = 0;
            for (ll index_j = 1; index_j <= m; index_j++) {
                row += matrix[index_i - 1][index_j - 1];
                prefix[index_i][index_j] = prefix[index_i - 1][index_j] + row;
            }
        }
    }

    ll get(ll x1, ll y1, ll x2, ll y2) {
        x1++;
        y1++;
        x2++;
        y2++;
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
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
