#include <bits/stdc++.h>
using namespace std;

int main() {
        cin.tie(0)->sync_with_stdio(0);
        int t; cin >> t;
        while (t--) {
                string s; cin >> s;
                cout << s.substr(0, s.length() - 2) << "i\n";
        }
}

