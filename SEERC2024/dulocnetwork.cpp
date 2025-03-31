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

    auto query = [&](vector<int> s) {
        vector<bool> used(n);
        for (int x : s) used[x] = 1;
        string str;
        for (int i = 0; i < n; i++) {
            str += char('0' + used[i]);
        }
        cout << "? " << str << "\n";
        cout.flush();
        int x;
        cin >> x;
        return x;
    };

    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        vector<int> tmp;
        tmp.push_back(i);
        deg[i] = query(tmp);
    }

    vector<int> s, unused;
    s.push_back(0);
    int degCombined = deg[0];
    for (int i = 1; i < n; i++) {
        unused.push_back(i);
    }

    while ((int) s.size() < n) {
        int l = 0, r = (int) unused.size() - 1, idx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            vector<int> curGroup;
            vector<int> combined = s;
            for (int i = l; i <= mid; i++) {
                combined.push_back(unused[i]);
                curGroup.push_back(unused[i]);
            }
            int res = query(combined);
            if (res < query(curGroup) + degCombined) {
                if (l == r) {
                    idx = mid;
                    degCombined = res;
                    s.push_back(unused[idx]);
                    unused.erase(unused.begin() + idx);
                    break;
                }
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        if (idx == -1) {
            cout << "! 0\n";
            cout.flush();
            return 0;
        }
    }

    cout << "! 1\n";
    
    return 0;
}
