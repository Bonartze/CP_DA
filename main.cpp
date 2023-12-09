#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<char> st;
        int brackets = 0;
        for (char& c: s) {
            if (c=='(') {
                brackets++;
                st.push(c);
            }
            else if (c==')' && brackets!=0) {
                brackets--;
                st.push(c);
            }
            else if (isalpha(c)) {
                st.push(c);
            }
        }
        auto st_size = st.size();
        string result;
        for (size_t i = 0;i<st_size; i++) {
            result+=st.top();
            st.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> board = {1, 2, 2};
    cout << sol.minRemoveToMakeValid("lee(t(c)o)de)");
}
