#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n, -1);
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                q.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }

    vector<ll> dist2(n, 0);
    int best = 0, secondBest = 0;
    for (int i = 0; i < n; i++) {
        dist2[i] = a[i] - b[i] * (dist[i] + 1);
        if (dist2[i] >= dist2[best]) {
            secondBest = best;
            best = i;
        } else if (dist2[i] > dist2[secondBest]) {
            secondBest = i;
        }
    }

    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        if (i != best) {
            ans[i] = dist2[best];
        } else {
            ans[i] = dist2[secondBest];
        }
    }

    vector<vector<int>> adj2(2 * n);
    for (int i = 0; i < n; i++) {
        for (int v : adj[i]) {
            if (dist[v] == dist[i] + 1) {
                adj2[i].push_back(v);
                adj2[i + n].push_back(v + n);
            } else if (dist[v] == dist[i]) {
                adj2[i].push_back(v + n);
                adj2[v].push_back(i + n);
            }
        }
    }

    auto dfs = [&](auto self, int u) -> void {
        for (int v : adj2[u]) {
        }
    };
    
    return 0;
}
