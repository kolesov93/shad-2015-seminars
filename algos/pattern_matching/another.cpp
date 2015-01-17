vector<size_t> calculate_z_function(const string& s) {
    vector<size_t> z(s.size());

    size_t l = 0, r = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (r > i) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}
