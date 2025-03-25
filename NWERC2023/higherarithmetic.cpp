#include <bits/stdc++.h>
#include <cmath>
#include <queue>
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

    int ones = 0, twos = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    if (n == 1) {
        cout << a[0] << endl;
        return 0;
    }

    vector<string> expressions;
    for (int i = 0; i < n; i++) {
        if (a[i] >= 3) {
            expressions.push_back(to_string(a[i]));
        } else if (a[i] == 1) {
            ones++;
        } else {
            twos++;
        }
    }

    while (ones && twos) {
        if (ones == 2 && twos == 1) {
            expressions.push_back("(1+1+2)");
            ones = 0, twos = 0;
        } else {
            expressions.push_back("(1+2)");
            ones--, twos--;
        }
    }

    if (!twos) {
        if (ones % 3 == 0) {
            for (int i = 0; i < ones / 3; i++) {
                expressions.push_back("(1+1+1)");
            }
        } else if (ones % 3 == 1) {
            if (ones == 1) {
                assert(!expressions.empty());
                auto x = expressions[0];
                expressions.erase(expressions.begin());
                expressions.push_back("(" + x + "+1)");
            } else {
                for (int i = 0; i < ones / 3 - 1; i++) {
                    expressions.push_back("(1+1+1)");
                }
                expressions.push_back("(1+1)");
                expressions.push_back("(1+1)");
            }
        } else {
            for (int i = 0; i < ones / 3; i++) {
                expressions.push_back("(1+1+1)");
            }
            expressions.push_back("(1+1)");
        }
    } else {
        for (int i = 0; i < twos; i++) {
            expressions.push_back("2");
        }
    }

    int e = expressions.size();
    for (int i = 0; i < e; i++) {
        cout << expressions[i] << "*\n"[i == e - 1];
    }

    return 0;
}
