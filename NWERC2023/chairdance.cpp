// incomplete
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

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }

    vector<bool> eliminated(n + 1);
    int add = 0, multiply = 1;
    int remain = n;

    while (q--) {
        char opt;
        int x;
        cin >> opt >> x;

        if (opt == '+') {
            add += x;
        } else if (opt == '*') {
            if (gcd(remain, x) > 1) {
                for (int i = 1; i <= n; i++) {
                    if (!eliminated[i]) {

                    }
                }
            } else {
                multiply = ((ll) x * multiply) % n;
                add = ((ll) x * add) % n;
            }
        } else {
            // who sits on chair x?
            // i * multiply + add = x (mod n)
            // i = (x - add) * multiply ^ (-1) (mod n)
            //
        }
    }
    
    return 0;
}
