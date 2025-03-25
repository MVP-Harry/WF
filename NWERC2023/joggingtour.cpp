#include <bits/stdc++.h>
#include <cmath>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

const int N = 12;
double d[N][N][N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    auto dist = [&](int i, int j, pair<double, double> angle) -> double {
        pair<double, double> x = {pts[j].first - pts[i].first, pts[j].second - pts[i].second};
        if ((ll) x.second * angle.first == (ll) x.first * angle.second) {
            return sqrt(x.first * x.first + x.second * x.second);
        } else {
            assert(x.first != 0 || x.second != 0);
            assert(angle.first != 0 || angle.second != 0);
            double dot = x.first * angle.first + x.second * angle.second;
            double theta = acos(dot / sqrt(x.first * x.first + x.second * x.second) / sqrt(angle.first * angle.first + angle.second * angle.second));
            return sqrt(x.first * x.first + x.second * x.second) * (abs(cos(theta)) + abs(sin(theta)));
        }
    };

    vector<vector<double>> dp(n, vector<double>(1 << n, 1e9));
    auto solve = [&](auto self, int i, int state, int x, int y) {
        if (abs(dp[i][state] - 1e9) > 1e-9) {
            return dp[i][state];
        }
        if (state == (1 << n) - 1) {
            return dp[i][state] = 0;
        }

        for (int j = 0; j < n; j++) {
            if (!((state >> j) & 1)) {
                dp[i][state] = min(dp[i][state], d[i][j][x][y] + self(self, j, state | (1 << j), x, y));
            }
        }
        return dp[i][state];
    };

    /*dbg(dist(0, 1, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/
    /*dbg(dist(0, 2, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/
    /*dbg(dist(0, 2, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/
    /*dbg(dist(2, 0, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/
    /*dbg(dist(1, 2, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/
    /*dbg(dist(2, 1, {pts[1].first - pts[0].first, pts[1].second - pts[0].second}));*/

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int m = k + 1; m < n; m++) {
                    d[i][j][k][m] = dist(i, j, {pts[m].first - pts[k].first, pts[m].second - pts[k].second});
                }
            }
        }
    }

    double ans = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ans = min(ans, solve(solve, k, (1 << k), i, j));
            }
            dp = vector(n, vector<double>(1 << n, 1e9));
        }
    }

    cout << fixed << setprecision(9);
    cout << ans << "\n";

    return 0;
}
