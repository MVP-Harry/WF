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
    cin.ignore();

    vector<pair<string, string>> names(n);
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        for (int j = 0; j < line.length(); j++) {
            if (isupper(line[j])) {
                names[i].first = line.substr(j);
                names[i].second = line;
                break;
            }
        }
    }
    sort(names.begin(), names.end());
    for (auto [_, x] : names) {
        cout << x << "\n";
    }
    
    return 0;
}
