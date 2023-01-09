#include <bits/stdc++.h>

using namespace std;

bool check(vector<int> L, vector<string> patterns, int &resLen) {
    for (auto &i : patterns.back()) {
        if (i >= 'a')
            resLen++;
        else
            resLen += L[i - 'A'];
    }
    for (int x = 0; x < patterns.size(); x++) {
        int currRes = 0;
        for (auto &i : patterns[x]) {
            if (i >= 'a')
                currRes++;
            else
                currRes += L[i - 'A'];
        }
        if (currRes != resLen) return true;
    }
    return false;
}

class MatchingPatterns {
   public:
    string solve(int N, vector<int> L, vector<string> patterns) {
        int resLen = 0;
        if (check(L, patterns, resLen)) return "";
        vector<vector<array<int, 2>>> grid(
            patterns.size(), vector<array<int, 2>>(resLen, {-1, -1}));
        vector<vector<char>> str(patterns.size(), vector<char>(resLen, '$'));
        vector<vector<array<int, 2>>> starts(N);
        queue<array<int, 2>> bfsQ;
        for (int x = 0; x < patterns.size(); x++) {
            for (int y = 0, ind = 0; ind < resLen; y++, ind++) {
                if (patterns[x][y] >= 'a') {
                    str[x][ind] = patterns[x][y];
                    bfsQ.push({x, ind});
                    continue;
                }
                int currVar = patterns[x][y] - 'A';
                starts[currVar].push_back({x, ind});
                for (int z = 0; z < L[currVar]; z++)
                    grid[x][ind + z] = {currVar, z};
                ind += L[currVar] - 1;
            }
        }

        while (!bfsQ.empty()) {
            auto &[currX, currY] = bfsQ.front();
            // cout << currX << ' ' << currY << '\n';
            auto currCh = str[currX][currY];
            bfsQ.pop();

            for (int x = 0; x < patterns.size(); x++) {
                if (str[x][currY] == '$') {
                    str[x][currY] = currCh;
                    bfsQ.push({x, currY});
                } else if (str[x][currY] != currCh)
                    return "";
            }
            auto &currGrid = grid[currX][currY];
            if (currGrid[0] == -1) continue;
            for (auto &[newX, tempY] : starts[currGrid[0]]) {
                auto newY = tempY + currGrid[1];
                for (int x = 0; x < patterns.size(); x++) {
                    // if (currX + currY == 0) {
                    // cout << x << ' ' << newY << '\n';
                    // }
                    if (str[x][newY] == '$') {
                        str[x][newY] = currCh;
                        bfsQ.push({x, newY});
                    } else if (str[x][newY] != currCh)
                        return "";
                }
            }
        }
        // for (auto &i : str) {
        // for (auto &j : i) cout << j << ' ';
        // cout << '\n';
        // }
        string ans = "";
        for (auto &i : str.front()) ans.push_back(i == '$' ? 'a' : i);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N);
    for (auto &i : v) cin >> i;
    vector<string> s;
    string nb;
    while (cin >> nb) {
        s.push_back(nb);
    }
    MatchingPatterns obj;
    cout << obj.solve(N, v, s);
    return 0;
}