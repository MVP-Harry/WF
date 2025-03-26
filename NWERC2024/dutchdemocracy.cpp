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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), greater<int>());

    int total = accumulate(a.begin(), a.end(), 0);
    int majority = total / 2 + 1;

    ll ans = 0;
    vector<ll> dp(n * 10000 + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = majority - 1; j >= 0; j--) {
            if (j + a[i] > total) continue;
            if (j + a[i] >= majority) {
                ans += dp[j];
            }
            dp[j + a[i]] += dp[j];
        }
    }
    cout << ans << "\n";
    
    return 0;
}
