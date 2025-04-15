#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

const int N = 1001;

int n;
vector<string> s;
int dp[N][N][4], vis[N][N][4];
vector<int> dx = {0, -1, 0, 1}; // right, up, left, down
vector<int> dy = {1, 0, -1, 0};

int dfs(int x, int y, int k) {
    /*dbg(x, y, k);*/
    if (dp[x][y][k] != 0) return dp[x][y][k];
    if (vis[x][y][k] && dp[x][y][k] == 0) return dp[x][y][k] = -1;
    vis[x][y][k] = 1;
    // k = 0 -> currently facing right -> down, right, up, left
    // k = 1 -> currently facing up -> right, up, left, down
    // k = 2 -> currently facing left -> up, left, down, right
    // k = 3 -> currently facing down -> left, down, right, up
    for (int i = 3; i <= 6; i++) {
        int newDir = (k + i) % 4;
        int nx = x + dx[newDir];
        int ny = y + dy[newDir];
        /*dbg(nx, ny);*/

        if (nx < 0 || nx >= n || ny < 0 || ny >= n) return dp[x][y][k] = 1;
        if (s[nx][ny] == '#') continue;

        int res = dfs(nx, ny, newDir);
        if (res != -1) return dp[x][y][k] = res + 1;
        else return dp[x][y][k] = -1;
    }
    return dp[x][y][k] = -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int q;
    cin >> n >> q;

    s = vector<string>(n);

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '#') {
                for (int k = 0; k < 4; k++) {
                    dp[i][j][k] = -1;
                    vis[i][j][k] = 0;
                }
            }
        }
    }

    /*dfs(1, 9, 1);*/
    /*dbg(dp[1][9][1]);*/
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 4; k++) {
                if (!vis[i][j][k]) {
                    dfs(i, j, k);
                }
            }
        }
    }

    /*for (int i = 0; i < n; i++) {*/
    /*    for (int j = 0; j < n; j++) {*/
    /*        for (int k = 0; k < 4; k++) {*/
    /*            dbg(i, j, k, dp[i][j][k]);*/
    /*        }*/
    /*    }*/
    /*}*/

    while (q--) {
        int x, y;
        char d;
        cin >> x >> y >> d;
        x--, y--;

        int k = 0;
        if (d == 'U') k = 1;
        else if (d == 'L') k = 2;
        else if (d == 'D') k = 3;
        cout << dp[x][y][k] << "\n";
    }
    
    return 0;
}
