#include <algorithm>
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
        int n, m;
        ll k;
        cin >> n >> k >> m;
        vector<char> alphabet;
        for (int i = 0; i < min(n, 10); i++) {
            alphabet.push_back(char('0' + i));
        }
        for (int i = 0; i < min(n - 10, 26); i++) {
            alphabet.push_back(char('A' + i));
        }
        for (int i = 0; i < m; i++) {
            char x;
            cin >> x;
            alphabet.erase(find(alphabet.begin(), alphabet.end(), x));
        }

        ll d = alphabet.size();
        string ans;
        while (k != 0) {
            ans += alphabet[k % d];
            k -= (k % d);
            k /= d;
        }
        reverse(ans.begin(), ans.end());
        cout << ans << "\n";
    }
    
    return 0;
}
