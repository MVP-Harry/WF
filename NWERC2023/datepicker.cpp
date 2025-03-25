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

    vector<bitset<24>> s(7);
    for (int i = 0; i < 7; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < 24; j++) {
            if (str[j] == '.') {
                s[i].set(23 - j);
            }
        }
    }
    int d, h;
    cin >> d >> h;

    vector<bitset<24>> hours;
    for (int i = 0; i < (1 << 24); i++) {
        bitset<24> x(i);
        if (x.count() == h) {
            hours.push_back(x);
        }
    }

    int ans = 0;
    for (auto x : hours) {
        vector<int> cnt;
        for (int i = 0; i < 7; i++) {
            cnt.push_back((x & s[i]).count());
        }
        sort(cnt.begin(), cnt.end());
        int sum = 0;
        for (int i = 6; i > 6 - d; i--) {
            sum += cnt[i];
        }
        ans = max(ans, sum);
    }

    cout << fixed << setprecision(6);
    cout << ((double) ans / (d * h)) << "\n";
    
    return 0;
}
