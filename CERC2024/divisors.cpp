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

    int T;
    cin >> T;

    while (T--) {
        ll n;
        cin >> n;

        auto check = [](ll x, ll y) {
            vector<int> cnt(10);
            while (x != 0) {
                cnt[x % 10]++;
                x /= 10;
            } 
            while (y != 0) {
                cnt[y % 10]--;
                y /= 10;
            }
            for (int i = 0; i <= 9; i++) {
                if (cnt[i] != 0) {
                    return false;
                }
            }
            return true;
        };

        int ans = 0;
        for (int i = 2; i <= 9; i++) {
            if (n % i == 0) {
                ll x = n / i;
                if (check(n, x)) {
                    ans++;
                }
            }
        }

        cout << ans << '\n';
    }
    
    return 0;
}
