#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

template<typename T>
vector<T> dijkstra(vector<vector<pair<int, T>>> adj, int s) {
    int n = (int) adj.size();
    vector<T> dist(n, 1e15);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    } 
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, l;
        cin >> u >> v >> l;
        u--, v--;
        adj[u].emplace_back(v, l);
        adj[v].emplace_back(u, l);
    }

    vector<ll> dist = dijkstra<ll>(adj, 0);
    vector<ll> distReversed = dijkstra<ll>(adj, n - 1);

    vector<pair<ll, double>> stores;
    for (int i = 0; i < k; i++) {
        int x;
        double p;
        cin >> x >> p;
        stores.emplace_back(dist[x - 1] + distReversed[x - 1], p);
    }
    sort(stores.begin(), stores.end());

    double ans = 0, remainingProb = 1;
    for (auto [d, p] : stores) {
        ans += d * p * remainingProb;
        remainingProb *= (1 - p);
        if (p == 1.0) {
            cout << fixed << setprecision(9);
            cout << ans << "\n";
            return 0;
        }
    }
    cout << "impossible\n";

    return 0;
}
