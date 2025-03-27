#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#ifdef LOCAL
    #include <bits/debug.h>
#else
    #define dbg(...)
#endif

bool check(vector<int> a) {
    vector<vector<int>> magic = {{0, 1, 2}, {6, 7, 8},
                                 {0, 4, 8}};
    vector<int> cnt(31);
    for (int i = 4; i < 9; i++) {
        if (a[i] < 0 || a[i] > 30) return false;
        cnt[a[i]]++;
        if (cnt[a[i]] >= 2) return false;
    }

    int ans = -1;
    for (auto entries : magic) {
        int sum = 0;
        for (int x : entries) {
            sum += a[x];
        }
        if (ans == -1) {
            ans = sum;
        } else {
            if (ans != sum) return false;
        }
    }
    return true;
}

vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    vector<int> a(9);
    vector<int> cnt(21);
    for (a[0] = 0; a[0] <= 30; a[0]++) {
        for (a[1] = 0; a[1] <= 30; a[1]++) {
            for (a[2] = 0; a[2] <= 30; a[2]++) {
                int sum = a[0] + a[1] + a[2];
                if (sum > 60) continue;
                for (a[3] = 0; a[3] <= sum; a[3]++) {
                    a[6] = sum - a[0] - a[3];
                    a[4] = sum - a[2] - a[6];
                    a[5] = sum - a[3] - a[4];
                    a[7] = sum - a[1] - a[4];
                    a[8] = sum - a[2] - a[5];
                    if (check(a)) {
                        assert(sum % 3 == 0);
                        cnt[sum / 3]++;
                        if (sum == 3) dbg(a);
                    }
                }
            }
        }
    }

    dbg(cnt);
    sieve(1e6 + 1);

    vector<int> dp(1e6 + 1);
    dp[1] = 1;
    for (int p : primes) {
        for (ll i = p, x = 1; i <= 1e6; i *= p, x++) {
            for (int j = 1e6 / i; j >= 1; j--) {
                dp[j * i] += dp[j] * cnt[x];
            }
        }
    }

    for (int i = 0; i <= 10; i++) {
        cout << i << ": " << dp[i] << "\n";
    }

    /*int q;*/
    /*cin >> q;*/
    /*while (q--) {*/
    /*    ll x;*/
    /*    cin >> x;*/
    /*    ll l = 1, r = 1e6, ans = 1;*/
    /*    while (l <= r) {*/
    /*        ll mid = (l + r) / 2;*/
    /*        if (mid * mid * mid <= x) {*/
    /*            ans = mid;*/
    /*            l = mid + 1;*/
    /*        } else {*/
    /*            r = mid - 1;*/
    /*        }*/
    /*    }*/
    /*    cout << dp[ans] << "\n";*/
    /*}*/
    
    return 0;
}
