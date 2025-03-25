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

    ll n, s;
    cin >> n >> s;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (s == 1) {
        cout << 1 << "\n";
        return 0;
    }

    sort(a.begin(), a.end());

    auto check = [&](ll x) -> bool {
        ll ones = 0, twos = 0;
        ll need = 0;
        for (ll i = 0; i < x - 2; i++) {
            if (a[i] % 3 == 0) {
                need += a[i] / 3;
            } else if (a[i] % 3 == 1) {
                need += a[i] / 3 + 1;
                if (a[i] > 3) ones++;
            } else {
                need += a[i] / 3 + 1;
                if (a[i] > 3) twos++;
            }
        }

        dbg(need, ones, twos);
        ll p = min(ones, twos);
        need -= p;
        ones -= p, twos -= p;
        need -= ones / 2;
        return need <= s - 2;
    };

    ll l = 1, r = n, ans = 1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << "\n";
    
    return 0;
}
