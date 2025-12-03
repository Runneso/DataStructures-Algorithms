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
#define MOD (1'000'000'000LL+7LL)
#define MOD_ (1'000'000'000+9)
#define BASE (911382323)
#define BASE_ (972663749)
#define EPS 1e-8
#define all(x) x.begin(), x.end()
#define print(x) for (auto element : x) cout << element << " ";
#define endl "\n"

#define I_AM_OUTSIDER = true;

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;
struct DSU {
    ll n;
    vector<ll> parent, rank;

    DSU(ll n) {
        parent.resize(n);
        rank.resize(n, 0);
        iota(all(parent), 0);
    }

    ll find_set(ll x) {
        if (parent[x] == x) return x;
        return parent[x] = find_set(parent[x]);
    }

    void unite(ll xx,ll yy) {
        ll x = find_set(xx);
        ll y = find_set(yy);

        if (x == y) {
            return;
        }

        if (rank[x] < rank[y]) {
            swap(x, y);
        }

        parent[y] = x;

        if (rank[x] == rank[y]) {
            rank[x]++;
        }
    }
};

ll Prim(vector<vector<pair<ll,ll> > > &graph) {
    const ll n = graph.size();

    ll length = 0, ans = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<pair<ll,ll> > > pq;
    DSU snm(n);

    for (auto [u, c]: graph[0]) {
        pq.push({c, u});
    }

    while (length < n - 1) {
        auto [cost, node] = pq.top();
        pq.pop();

        if (snm.find_set(0) != snm.find_set(node)) {
            snm.unite(0, node);
            ans += cost;
            length++;
            for (auto [next, cost]: graph[node]) {
                if (snm.find_set(next) != snm.find_set(node)) {
                    pq.push({cost, next});
                }
            }
        }
    }

    return ans;
}

ll Kruskal(vector<vector<pair<ll,ll> > > &graph) {
    const ll n = graph.size();

    ll length = 0, ans = 0;
    vector<tuple<ll,ll,ll> > edges;
    DSU snm(n);

    for (ll node = 0; node < n; node++) {
        for (auto [next,cost]: graph[node]) {
            if (node < next) {
                edges.push_back({cost, node, next});
            }
        }
    }

    sort(all(edges));

    for (auto [cost, u,v]: edges) {
        if (snm.find_set(u) != snm.find_set(v)) {
            snm.unite(u, v);
            ans += cost;
            length++;
        }

        if (length == n - 1) {
            break;
        }
    }

    return ans;
}


ll Boruvka(vector<vector<pair<ll,ll> > > &graph) {
    const ll n = graph.size();

    ll components = n, ans = 0;
    DSU snm(n);
    vector<pair<ll,ll> > best(n);

    while (components > 1) {
        fill(all(best), make_pair(LLONG_MAX, -1));

        for (ll node = 0; node < n; node++) {
            ll parent = snm.find_set(node);

            for (auto [next, cost]: graph[node]) {
                if (snm.find_set(parent) != snm.find_set(next)) {
                    if (best[parent].first > cost) {
                        best[parent] = {cost, next};
                    }
                }
            }
        }

        for (ll node = 0; node < n; node++) {
            if (snm.find_set(node) != node) {
                continue;
            }

            if (best[node].second != -1) {
                ans += best[node].first;
                snm.unite(node, best[node].second);
                components--;
            }
        }
    }

    return ans;
}

void solution() {
    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll,ll> > > graph(n);

    for (ll index = 0; index < m; index++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        graph[u].push_back({v, c});
        graph[v].push_back({u, c});
    }
    cout << Boruvka(graph) << endl;
}
