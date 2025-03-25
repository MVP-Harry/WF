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

    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    int na = to_string(a).length();
    dbg(na);
    ll tmp = a;
    ll g = gcd(c, d);
    c /= g, d /= g;

    vector<int> da;
    for (int i = 0; i < na; i++) {
        da.push_back(tmp % 10); 
        tmp /= 10;
    }
    reverse(da.begin(), da.end());

    unordered_map<ll, int> possible_b;
    string sb = to_string(b);
    int nb = sb.length();
    for (int i = 1; i < (1 << nb); i++) {
        ll x = 0;
        int first_d = -1;
        for (int b = 0; b < nb; b++) {
            if ((i >> b) & 1) {
                x = x * 10 + sb[b] - '0';
                if (first_d == -1) first_d = sb[b] - '0';
            }
        }
        if (first_d == 0) continue;
        possible_b[x] = 1;
    }

    auto check = [&](ll x, ll y, int bits) -> bool {
        string sx = to_string(x);
        string sy = to_string(y);
        if (sx.length() > sy.length()) {
            return false;
        } else {
            vector<int> cnt(10);
            for (int i = 0; i < na; i++) {
                if (!((bits >> i) & 1)) {
                    cnt[da[i]]++;
                }
            }
            if (possible_b[x] != 1) return false;
            for (char c : sx) cnt[c - '0']++;
            for (char c : sb) cnt[c - '0']--;
            for (int i = 0; i < 10; i++) {
                if (cnt[i] != 0) return false;
            }
            return true;
        }
    };

    for (int i = 1; i < (1 << na); i++) {
        ll x = 0;
        int first_d = -1;
        for (int b = 0; b < na; b++) {
            if ((i >> b) & 1) {
                x = x * 10 + da[b];
                if (first_d == -1) first_d = da[b];
            }
        }
        if (first_d == 0) continue;
        dbg(x);

        if (x % c == 0) {
            ll bp = x / c;
            if ((1e18) / bp < d) continue;
            bp *= d;
            if (check(bp, b, i)) {
                cout << "possible\n";
                cout << x << " " << bp << "\n";
                return 0;
            }
        }
    }

    cout << "impossible\n";
    
    return 0;
}
