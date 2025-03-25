#include <bits/stdc++.h>
#include <cassert>
#include <cmath>
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

    int n, k;
    cin >> n >> k;

    auto query = [&](int x, int y) -> int {
        cout << x + 1 << " " << y + 1 << endl;
        cout.flush();
        string s;
        cin >> s;
        if (s == "hit") return 1;
        else if (s == "sunk") return 2;
        return 0;
    };

    auto guess = [&](int x, int y) -> bool {
        for (int i = x - 1; i >= max(0, x - 4); i--) {
            int res = query(i, y);
            if (res == 2) return true;
            if (res == 0) break;
        }
        for (int i = x + 1; i <= min(x + 4, n - 1); i++) {
            int res = query(i, y);
            if (res == 2) return true;
            if (res == 0) break;
        }
        for (int i = y - 1; i >= max(0, y - 4); i--) {
            int res = query(x, i);
            if (res == 2) return true;
            if (res == 0) break;
        }
        for (int i = y + 1; i <= min(y + 4, n - 1); i++) {
            int res = query(x, i);
            if (res == 2) return true;
            if (res == 0) break;
        }
        return false;
    };

    for (int i = 0; i < n; i++) {
        int cur = 0;
        while (cur < n) {
            int x = min(n - 1, cur + 4);
            int res = query(i, x);
            if (res != 0) {
                bool success = guess(i, x);
                assert(success);
                k--;
                if (k == 0) return 0;
            }
            cur += 9;
        }
    }

    for (int i = 0; i < n; i++) {
        int cur = 0;
        while (cur < n) {
            int x = min(n - 1, cur + 4);
            int res = query(x, i);
            if (res != 0) {
                bool success = guess(x, i);
                assert(success);
                k--;
                if (k == 0) return 0;
            }
            cur += 9;
        }
    }

    return 0;
}
