#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

const int N = 501;
bool dp[N][N][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<vector<pair<int, int>>> moves(2);
    for (int i = 0; i < 2; i++) {
        int a, b;
        cin >> a >> b;
        for (int s1 : {-1, 1}) {
            for (int s2 : {-1, 1}) {
                moves[i].push_back({s1 * a, s2 * b});
                moves[i].push_back({s1 * b, s2 * a});
            }
        }
    }

    auto dfs = [&](auto self, int x, int y, int t) -> void {
        if (dp[x][y][t]) return;
        dp[x][y][t] = true;
        for (auto [i, j] : moves[t]) {
            if (x + i >= 0 && x + i < n && y + j >= 0 && y + j < n) {
                self(self, x + i, y + j, t ^ 1);
            }
        }
    };

    dfs(dfs, 0, 0, 0);
    dfs(dfs, 0, 0, 1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j][0] || dp[i][j][1]) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
