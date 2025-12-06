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

struct Dinic {
    static constexpr ll INF = (1LL<<62);

    struct Edge {
        ll to, rev;
        ll cap;
    };

    struct OrigEdgeRef {
        ll from, idx;
        ll cap0;
    };

    ll n;
    vector<vector<Edge>> g;
    vector<ll> level, it;
    vector<OrigEdgeRef> orig;

    Dinic(ll n_ = 0) { init(n_); }

    void init(ll n_) {
        n = n_;
        g.assign((size_t)n, {});
        level.assign((size_t)n, 0);
        it.assign((size_t)n, 0);
        orig.clear();
    }

    void add_edge(ll u, ll v, ll cap) {
        Edge a{v, (ll)g[(size_t)v].size(), cap};
        Edge b{u, (ll)g[(size_t)u].size(), 0};
        g[(size_t)u].push_back(a);
        g[(size_t)v].push_back(b);
        orig.push_back({u, (ll)g[(size_t)u].size() - 1, cap});
    }

    void add_undirected(ll u, ll v, ll cap) {
        add_edge(u, v, cap);
        add_edge(v, u, cap);
    }

    bool bfs(ll s, ll t) {
        fill(all(level), -1);
        queue<ll> q;
        level[(size_t)s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for (auto &e : g[(size_t)v]) {
                if (e.cap > 0 && level[(size_t)e.to] == -1) {
                    level[(size_t)e.to] = level[(size_t)v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[(size_t)t] != -1;
    }

    ll dfs(ll v, ll t, ll pushed) {
        if (!pushed) return 0;
        if (v == t) return pushed;
        for (ll &i = it[(size_t)v]; i < (ll)g[(size_t)v].size(); i++) {
            Edge &e = g[(size_t)v][(size_t)i];
            if (e.cap > 0 && level[(size_t)e.to] == level[(size_t)v] + 1) {
                ll tr = dfs(e.to, t, min(pushed, e.cap));
                if (!tr) continue;
                e.cap -= tr;
                g[(size_t)e.to][(size_t)e.rev].cap += tr;
                return tr;
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(all(it), 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }

    vector<ll> min_cut_side(ll s) {
        vector<ll> vis((size_t)n, 0);
        queue<ll> q;
        vis[(size_t)s] = 1;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for (auto &e : g[(size_t)v]) {
                if (e.cap > 0 && !vis[(size_t)e.to]) {
                    vis[(size_t)e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }

    tuple<vector<ll>, vector<pair<ll,ll>>, ll> min_cut(ll s) {
        auto side = min_cut_side(s);
        vector<pair<ll,ll>> cut_edges;
        ll cut_value = 0;

        for (auto &r : orig) {
            ll u = r.from;
            Edge &e = g[(size_t)u][(size_t)r.idx];
            ll v = e.to;
            if (side[(size_t)u] == 1 && side[(size_t)v] == 0 && r.cap0 > 0) {
                cut_edges.push_back({u, v});
                cut_value += r.cap0;
            }
        }
        return {side, cut_edges, cut_value};
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
