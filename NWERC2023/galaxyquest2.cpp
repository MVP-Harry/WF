#include <bits/stdc++.h>
#include <ctime>
#include <iomanip>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

struct Planet {
    ll x, y, z;
};

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

    int n, m, q;
    cin >> n >> m >> q;

    vector<Planet> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z;
    }

    vector<vector<pair<int, double>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        double d = sqrt((a[u].x - a[v].x) * (a[u].x - a[v].x) + 
                        (a[u].y - a[v].y) * (a[u].y - a[v].y) + 
                        (a[u].z - a[v].z) * (a[u].z - a[v].z));
        adj[u].push_back({v, sqrt(d)});
        adj[v].push_back({u, sqrt(d)});
    }

    dbg(adj);

    auto dist = dijkstra<double>(adj, 0);
    cout << fixed << setprecision(9);
    while (q--) {
        int planet, timelimit;
        cin >> planet >> timelimit;
        planet--;
        double x = timelimit / dist[planet];
        if (x < 2) {
            cout << "impossible\n";
        } else {
            double c = (x - sqrt(x * x - 4)) / 2;
            cout << 2 * c * dist[planet] << "\n";
        }
    }

    return 0;
}
