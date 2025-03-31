#include <bits/stdc++.h>
#include <unistd.h>
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

    unordered_map<int, int> previous;
    vector<int> a(n), closest(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (previous.count(a[i])) {
            closest[i] = previous[a[i]];
        }
        previous[a[i]] = i;
    }

    int ans = 0;
    vector<pair<int, int>> dp(n);
    dp[0] = {1, 0};
    for (int i = 1; i < n; i++) {
        if (closest[i] != -1) {
            dp[i].second = dp[closest[i]].first + 1;
        }
        dp[i].first = max(1 + dp[i - 1].second, dp[i].second);
        ans = max(ans, dp[i].second);
    }
    dbg(dp);
    cout << ans << "\n";
    
    return 0;
}
