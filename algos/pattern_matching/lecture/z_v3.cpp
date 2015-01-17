vector<size_t> calculate_z(const string& s) {
    vector<size_t> z(s.size());

    size_t left = 0, right = 0;
    for (size_t i = 1; i < z.size(); ++i) {
        if (i < right) {
            z[i] = min(right - i, z[i - left]);
        }
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }

    return z;
}
