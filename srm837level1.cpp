#include <bits/stdc++.h>

using namespace std;

class StairsFromBlocks {
   public:
    long build(vector<int> W, vector<int> H) {
        int n = W.size();
        vector<array<long long, 2>> v(n);
        for (int x = 0; x < n; x++) {
            v[x] = {H[x], W[x]};
        }
        sort(v.begin(), v.end());
        long long lastH = 0;
        long long ans = 0;
        for (auto &[currH, currW] : v) {
            if (currH >= lastH + 1) {
                ans += currH * (currH - 1) / 2 - lastH * (lastH + 1) / 2;
                auto newH = currH + currW - 1;
                ans += (newH) * (newH + 1) / 2 - (currH) * (currH - 1) / 2;
                ans -= currH * currW;
                lastH = newH;
            } else {
                auto elevate = lastH - currH;
                ans += currW * elevate;
                ans += currW * (currW + 1) / 2;
                lastH = lastH + currW;
            }
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v1(N);
    vector<int> v2(N);
    for (auto &i : v1) cin >> i;

    for (auto &i : v2) cin >> i;
    StairsFromBlocks obj;
    cout << obj.build(v1, v2);
    return 0;
}