vector<size_t> calculate_z(const string& s) {
    vector<size_t> z(s.size());

    size_t l = 0, r = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (r <= i) {
            l = r = i;
            while (r < s.size() && s[r] == s[r - l]) ++r;
            z[i] = r - l;
        } else {
            if (z[i - l] < r - i) {
                z[i] = z[i - l];
                continue;
            }
            z[i] = r - i;
            while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }

    return z;
}