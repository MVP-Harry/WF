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

    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dbg(adj[1]);
    vector<vector<int>> dp(n, vector<int>(2));
    auto dfs = [&](auto self, int u, int p) -> void {
        int sum = 0;
        vector<int> dif;
        for (int v : adj[u]) {
            if (v != p) {
                self(self, v, u);
                sum += dp[v][0];
                dif.push_back(dp[v][1] - dp[v][0]);
            }
        }
        dp[u][0] = sum + 2;
        dp[u][1] = sum;
        sort(dif.begin(), dif.end());
        if (u == 1) {
            dbg(sum, dif);
        }
        int penalty = 1, tot = 0;
        for (int x : dif) {
            tot += x;
            dp[u][0] = min(dp[u][0], sum + penalty + tot);
            penalty += 2;
        }
    };

    dfs(dfs, 0, 0);
    dbg(dp);
    cout << dp[0][0] << "\n";

    return 0;
}
