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

struct Edge {
    ll from, to, cap, flow = 0;

    Edge(ll from, ll to, ll cap) : from(from), to(to), cap(cap) {
    }
};

struct Dinic {
    vector<Edge> edges;
    vector<vector<ll> > graph;
    ll n = 0, m = 0, Q = 30;
    ll s, t;
    vector<ll> level, ptrs;
    queue<ll> q;

    Dinic(ll n, ll s, ll t): n(n), s(s), t(t) {
        edges.reserve(2 * n);
        graph.resize(n);
        level.resize(n);
        ptrs.resize(n);
    }

    void add_edge(ll from, ll to, ll cap) {
        edges.push_back({from, to, cap});
        edges.push_back({to, from, cap}); // use cap of undirected graph
        graph[from].push_back(m);
        graph[to].push_back(m + 1);
        m += 2;
    }


    bool bfs(ll limit) {
        prepare();
        while (!q.empty()) {
            ll node = q.front();
            q.pop();

            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                ll remaining = edge.cap - edge.flow;
                if (remaining == 0 || remaining < limit) {
                    continue;
                }
                if (level[edge.to] != -1) {
                    continue;
                }
                level[edge.to] = 1 + level[edge.from];
                q.push(edge.to);
            }
        }
        return level[t] != -1;
    }

    ll dfs(ll node, ll minimum, ll limit) {
        if (minimum == 0) {
            return 0;
        }
        if (node == t) {
            return minimum;
        }

        for (ll &ptr = ptrs[node]; ptr < graph[node].size(); ptr++) {
            ll edge_id = graph[node][ptr];
            Edge &edge = edges[edge_id];
            ll remaining = edge.cap - edge.flow;

            if (level[edge.to] != level[edge.from] + 1) {
                continue;
            }
            if (remaining < limit) {
                continue;
            }

            ll pushed = dfs(edge.to, min(minimum, remaining), limit);

            if (pushed == 0) {
                continue;
            }

            edges[edge_id].flow += pushed;
            edges[edge_id ^ 1].flow -= pushed;
            return pushed;
        }

        return 0;
    }

    void prepare() {
        fill(all(level), -1);
        fill(all(ptrs), 0);
        level[s] = 0;
        q.push(s);
    }

    void compute() {
        for (ll delta = 1LL << Q; delta > 0; delta >>= 1) {
            while (bfs(delta)) {
                while (dfs(s,LLONG_MAX, delta)) {
                }
            }
        }
    }

    ll max_flow() {
        ll flow = 0;
        for (ll edge_id: graph[s]) {
            if (edges[edge_id].flow > 0) {
                flow += edges[edge_id].flow;
            }
        }
        return flow;
    }

    vector<ll> min_cut() {
        vector<ll> cut;
        vector<bool> visited(n, false);

        function<void(ll)> cut_dfs = [&](ll node) {
            visited[node] = true;
            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                if (!visited[edge.to] && edge.cap > edge.flow) {
                    cut_dfs(edge.to);
                }
            }
        };

        cut_dfs(s);

        for (ll index = 0; index < m; index += 2) {
            Edge &edge = edges[index];
            if (visited[edge.from] != visited[edge.to]) {
                cut.push_back(index);
            }
        }

        return cut;
    }
};
