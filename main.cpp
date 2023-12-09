#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void LCS(int m, int n, vector<string> str1, vector<string> str2, vector<int> &LL) {
    int k[2][n + 1];
    int i, j;
    for (j = 0; j < (n + 1); j++) k[1][j] = 0;

    for (i = 0; i < m; i++) {
        for (j = 0; j < (n + 1); j++) k[0][j] = k[1][j];

        for (j = 1; j < (n + 1); j++) {
            if (str1[i] == str2[j - 1]) k[1][j] = k[0][j - 1] + 1;
            else k[1][j] = max(k[1][j - 1], k[0][j]);
        }
    }
    for (j = 0; j < (n + 1); j++)
        LL[j] = k[1][j];
}

vector<string> Hirschberg_LCS(int m, int n, vector<string> str1, vector<string> str2, vector<string> lcs) {
    if (n == 0) {
        return {};
    } else {
        if (m == 1) {
            auto found = find(str2.begin(), str2.end(), str1[0]);
            if (found != end(str2))
                lcs.push_back(str1[0]);
            else
                lcs.clear();
            return lcs;
        }
    }

    vector<int> l1(n + 1), l2(n + 1);
    int i = (int) (m / 2);
    LCS(i, n, {str1.begin(), str1.begin() + i}, str2, l1);

    vector<string> str1_rev, str2_rev;
    vector<string>::reverse_iterator rev_iter;

    for (rev_iter = str1.rbegin(); rev_iter < str1.rend(); rev_iter++)
        str1_rev.push_back(*rev_iter);

    for (rev_iter = str2.rbegin(); rev_iter < str2.rend(); rev_iter++)
        str2_rev.push_back(*rev_iter);
    LCS(i + 1, n, {str1_rev.begin(), str1_rev.begin() + m - i}, str2_rev, l2);

    int max = 0, k = 0;
    for (int j = 0; j < (n + 1); j++) {
        if ((l1[j] + l2[n - j]) > max) {
            max = l1[j] + l2[n - j];
            k = j;
        }
    }
    vector<string> lcs1, lcs2;

    if (i == 0) i++;
    auto a = Hirschberg_LCS(i, k, {str1.begin(), str1.begin() + i}, {str2.begin(), str2.begin() + k}, lcs1);
    auto b = Hirschberg_LCS(m - i, n - k, {str1.begin() + i, str1.begin() + m}, {str2.begin() + k, str2.begin() + n},
                            lcs2);
    for (auto &be: b)
        a.push_back(be);
    return a;
}

int main() {
    ifstream f("input.txt");
    string temp;
    vector<string> words1;
    vector<string> words2;
    getline(f, temp);
    stringstream s1(temp);
    getline(f, temp);
    stringstream s2(temp);
    string word;
    while (s1 >> word) {
        words1.push_back(std::move(word));
    }
    while (s2 >> word) {
        words2.push_back(std::move(word));
    }
    vector<string> lcs;
    auto r = Hirschberg_LCS(words2.size(), words1.size(), words2, words1, lcs);
    cout << r.size() << endl;
    for (auto &a: r)
        cout << a << ' ';
}