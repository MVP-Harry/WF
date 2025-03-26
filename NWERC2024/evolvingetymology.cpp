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

    ll n, k;
    string s;
    cin >> n >> k >> s;

    ll mod = 1;
    if (k <= 30) {
        for (ll i = 0; i < k; i++) {
            mod *= 2;
        }
        mod %= n;
    } else {
        ll tmp = n, mul = 1;
        while (tmp % 2 == 0) {
            tmp /= 2;
            mul *= 2;
            k--;
        }

        auto binaryExpo = [](auto self, ll p, ll m) -> ll {
            if (p == 0) return 1;
            ll res = self(self, p / 2, m);
            if (p % 2 == 0) return res * res % m;
            return ((res * res) % m) * 2 % m;
        };

        mod = mul * binaryExpo(binaryExpo, k, tmp);
    }

    ll cur = 0;
    for (ll i = 0; i < n; i++) {
        cout << s[cur];
        cur = (cur + mod) % n;
    }
    cout << "\n";
    
    return 0;
}
