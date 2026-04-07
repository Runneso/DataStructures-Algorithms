struct Ford_Fulkerson {
    struct Edge {
        ll from, to, cap, flow;
    };

    ll n, m, s, t;
    ll edge_id = 0;
    vector<Edge> edges;
    vector<vector<ll> > graph;

    Ford_Fulkerson(ll n, ll m, ll s, ll t) : n(n), m(m), s(s), t(t) {
        edges.resize(2 * m);
        graph.resize(n);
    }

    void add_edge(ll u, ll v, ll cap, bool directed = true) {
        if (directed) {
            edges[edge_id] = {u, v, cap, 0};
            edges[edge_id ^ 1] = {v, u, 0, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        } else {
            edges[edge_id] = {u, v, cap, 0};
            edges[edge_id ^ 1] = {v, u, cap, 0};
            graph[u].push_back(edge_id);
            graph[v].push_back(edge_id ^ 1);
            edge_id += 2;
        }
    }

    ll max_flow() {
        vector<bool> visited(n, false);
        function<ll(ll,ll)> dfs = [&](ll node, ll flow) {
            if (node == t) {
                return flow;
            }
            visited[node] = true;
            for (ll edge_id: graph[node]) {
                Edge &edge = edges[edge_id];
                Edge &reverse_edge = edges[edge_id ^ 1];
                if (visited[edge.to]) {
                    continue;
                }
                if (edge.cap - edge.flow > 0) {
                    ll delta = dfs(edge.to, min(flow, edge.cap - edge.flow));
                    if (delta > 0) {
                        edge.flow += delta;
                        reverse_edge.flow -= delta;
                        return delta;
                    }
                }
            }
            return 0LL;
        };

        while (true) {
            fill(all(visited), false);
            ll delta = dfs(s, LLONG_MAX);
            if (delta == 0) {
                break;
            }
        }

        ll flow = 0;
        for (ll edge_id: graph[s]) {
            flow += edges[edge_id].flow;
        }
        return flow;
    }
};
