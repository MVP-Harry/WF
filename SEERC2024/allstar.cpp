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

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 0;
    for (int i = 0; i < n; i++) {
        if ((int) adj[i].size() > (int) adj[root].size()) {
            root = i;
        }
    }
    vector<bool> connected(n);
    queue<int> q;
    connected[root] = true;
    for (int v : adj[root]) {
        connected[v] = true;
        q.push(v);
    }

    cout << n - 1 - (int) adj[root].size() << '\n';
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!connected[v]) {
                cout << root + 1 << " " << u + 1 << " " << v + 1 << "\n";
                connected[v] = true;
                q.push(v);
            }
        }
    }
    
    return 0;
}
