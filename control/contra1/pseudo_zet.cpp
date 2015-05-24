vector<size_t> just_do_it(const string& s) {
    vector<size_t> ans(s.size());

    size_t a = 0, b = 0;
    for (size_t i = 1; i < ans.size(); ++i) {
        if (b <= i) {
            a = b = i;
            while (b < s.size() && s[b] == s[b - a]) ++b;
            ans[i] = b - a;
        } else {
            if (ans[i - a] < b - i) {
                ans[i] = ans[i - a];
                continue;
            }
            ans[i] = b - i;
            while (i + ans[i] < s.size() && s[i + ans[i]] == s[ans[i]]) {
                ++ans[i];
            }
            if (i + ans[i] > b) {
                a = i;
                b = i + ans[i];
            }
        }
    }

    return ans;
}
